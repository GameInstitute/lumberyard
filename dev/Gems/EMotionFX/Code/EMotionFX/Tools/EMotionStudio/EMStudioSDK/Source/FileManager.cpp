/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include "FileManager.h"
#include <MCore/Source/LogManager.h>
#include <MCore/Source/FileSystem.h>
#include <QFileDialog>
#include <QString>
#include <QTranslator>
#include <QMessageBox>
#include <QDateTime>
#include "EMStudioManager.h"
#include "MainWindow.h"
#include <EMotionFX/Source/EMotionFXManager.h>
#include <EMotionFX/Source/MotionManager.h>
#include <EMotionFX/Source/ActorManager.h>
#include <EMotionFX/Source/AnimGraphManager.h>
#include <EMotionFX/CommandSystem/Source/SelectionList.h>
#include <EMotionFX/CommandSystem/Source/MotionSetCommands.h>
#include <EMotionFX/CommandSystem/Source/ActorCommands.h>
#include <EMotionFX/CommandSystem/Source/AnimGraphCommands.h>

#include <AzCore/IO/FileIO.h>
#include <AzCore/IO/SystemFile.h>

#include <AzFramework/API/ApplicationAPI.h>

#include <Source/Integration/Assets/ActorAsset.h>
#include <Source/Integration/Assets/MotionAsset.h>
#include <Source/Integration/Assets/MotionSetAsset.h>
#include <Source/Integration/Assets/AnimGraphAsset.h>

#include <AzToolsFramework/AssetBrowser/AssetSelectionModel.h>
#include <AzToolsFramework/API/ToolsApplicationAPI.h>
#include <AzToolsFramework/API/EditorAssetSystemAPI.h>


namespace EMStudio
{
    FileManager::FileManager(QWidget* parent)
        : QObject(parent)
    {
        mLastActorFolder        = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        mLastMotionSetFolder    = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        mLastAnimGraphFolder    = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        mLastWorkspaceFolder    = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        mLastNodeMapFolder      = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();

        // Connect to the asset catalog bus for product asset changes.
        AzFramework::AssetCatalogEventBus::Handler::BusConnect();

        // Connect to the asset system bus for source asset changes.
        AzToolsFramework::AssetSystemBus::Handler::BusConnect();
    }


    FileManager::~FileManager()
    {
        AzFramework::AssetCatalogEventBus::Handler::BusDisconnect();
        AzToolsFramework::AssetSystemBus::Handler::BusDisconnect();
    }


    AZStd::string FileManager::GetAssetFilenameFromAssetId(const AZ::Data::AssetId& assetId)
    {
        AZStd::string filename;

        AZStd::string assetCachePath = AZ::IO::FileIOBase::GetInstance()->GetAlias("@assets@");
        AzFramework::StringFunc::AssetDatabasePath::Normalize(assetCachePath);

        AZStd::string relativePath;
        EBUS_EVENT_RESULT(relativePath, AZ::Data::AssetCatalogRequestBus, GetAssetPathById, assetId);
        AzFramework::StringFunc::AssetDatabasePath::Join(assetCachePath.c_str(), relativePath.c_str(), filename, true);
        
        return filename;
    }


    bool FileManager::IsAssetLoaded(const char* filename)
    {
        AZStd::string extension;
        AzFramework::StringFunc::Path::GetExtension(filename, extension, false /* include dot */);

        if (AzFramework::StringFunc::Equal(extension.c_str(), "motion"))
        {
            const AZ::u32 motionCount = EMotionFX::GetMotionManager().GetNumMotions();
            for (AZ::u32 i = 0; i < motionCount; ++i)
            {
                EMotionFX::Motion* motion = EMotionFX::GetMotionManager().GetMotion(i);
                if (motion->GetIsOwnedByRuntime())
                {
                    continue;
                }

                if (AzFramework::StringFunc::Equal(filename, motion->GetFileName()))
                {
                    return true;
                }
            }
        }

        if (AzFramework::StringFunc::Equal(extension.c_str(), "actor"))
        {
            const AZ::u32 actorCount = EMotionFX::GetActorManager().GetNumActors();
            for (AZ::u32 i = 0; i < actorCount; ++i)
            {
                EMotionFX::Actor* actor = EMotionFX::GetActorManager().GetActor(i);
                if (actor->GetIsOwnedByRuntime())
                {
                    continue;
                }

                if (AzFramework::StringFunc::Equal(filename, actor->GetFileName()))
                {
                    return true;
                }
            }
        }

        return false;
    }


    void FileManager::OnCatalogAssetChanged(const AZ::Data::AssetId& assetId)
    {
        const AZStd::string filename = GetAssetFilenameFromAssetId(assetId);

        // Skip re-loading the file, in case it not loaded currently.
        if (!IsAssetLoaded(filename.c_str()))
        {
            return;
        }

        AZ_Printf("", "OnCatalogAssetChanged: assetId='%s' file='%s'", assetId.ToString<AZStd::string>().c_str(), filename.c_str());

        // De-bounce cloned events for the same file.
        // Get the canonical asset id based on the filename to filter out all events for the legacy asset ids.
        // Multiple events get sent for the same file path as multiple asset ids can exist. The canonical asset id will be unique and is the latest version.
        AZ::Data::AssetInfo assetInfo;
        AZ::Data::AssetCatalogRequestBus::BroadcastResult(assetInfo, &AZ::Data::AssetCatalogRequestBus::Events::GetAssetInfoById, assetId);
        if (!assetInfo.m_assetId.IsValid() || assetInfo.m_assetId != assetId)
        {
            AZ_Printf("", "   + Skipping file. (Canonical assetId='%s')", assetInfo.m_assetId.ToString<AZStd::string>().c_str());
            return;
        }

        AZ_Printf("", "   + Reloading file. (Canonical assetId='%s')", assetInfo.m_assetId.ToString<AZStd::string>().c_str());

        // Spawn the command for reloading the file.
        GetMainWindow()->LoadFile(filename.c_str(), 0, 0, false, true);

        // Show notification.
        AZStd::string notificationMessage;
        AzFramework::StringFunc::Path::GetFileName(filename.c_str(), notificationMessage);
        notificationMessage += " updated";
        GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_SUCCESS, notificationMessage.c_str());
    }


    void FileManager::OnCatalogAssetAdded(const AZ::Data::AssetId& assetId)
    {
        // Do the same as for assets that changed because an asset could be loaded while the asset is temporarily gone.
        // Case: Re-exporting an fbx from Maya
        // 1. The fbx file first gets removed. The asset processor also removes all products then.
        // 2. Maya saves the new fbx. The asset processor generates a new product using the same file path.
        // What we do in this case is, ignoring the remove operation and re-linking the asset when it gets recreated.
        OnCatalogAssetChanged(assetId);
    }


    void FileManager::OnCatalogAssetRemoved(const AZ::Data::AssetId& assetId)
    {
    }


    bool FileManager::IsSourceAssetLoaded(const char* filename)
    {
        AZStd::string extension;
        AzFramework::StringFunc::Path::GetExtension(filename, extension, false /* include dot */);

        if (AzFramework::StringFunc::Equal(extension.c_str(), "motionset"))
        {
            const AZ::u32 motionSetCount = EMotionFX::GetMotionManager().GetNumMotionSets();
            for (AZ::u32 i = 0; i < motionSetCount; ++i)
            {
                EMotionFX::MotionSet* motionSet = EMotionFX::GetMotionManager().GetMotionSet(i);
                if (motionSet->GetIsOwnedByRuntime())
                {
                    continue;
                }

                if (AzFramework::StringFunc::Equal(filename, motionSet->GetFilename()))
                {
                    return true;
                }
            }
        }

        if (AzFramework::StringFunc::Equal(extension.c_str(), "animgraph"))
        {
            const AZ::u32 animGraphCount = EMotionFX::GetAnimGraphManager().GetNumAnimGraphs();
            for (AZ::u32 i = 0; i < animGraphCount; ++i)
            {
                EMotionFX::AnimGraph* animGraph = EMotionFX::GetAnimGraphManager().GetAnimGraph(i);
                if (animGraph->GetIsOwnedByRuntime())
                {
                    continue;
                }

                if (AzFramework::StringFunc::Equal(filename, animGraph->GetFileName()))
                {
                    return true;
                }
            }
        }

        return false;
    }


    void FileManager::SourceFileChanged(AZStd::string relativePath, AZStd::string scanFolder, AZ::TypeId sourceTypeId)
    {
        AZStd::string filename;
        AZStd::string assetSourcePath = AZ::IO::FileIOBase::GetInstance()->GetAlias("@devassets@");
        AzFramework::StringFunc::AssetDatabasePath::Normalize(assetSourcePath);
        AzFramework::StringFunc::AssetDatabasePath::Join(assetSourcePath.c_str(), relativePath.c_str(), filename, true);

        // Skip re-loading the file, in case it not loaded currently.
        if (!IsSourceAssetLoaded(filename.c_str()))
        {
            return;
        }

        // Spawn the command for reloading the file.
        GetMainWindow()->LoadFile(filename.c_str(), 0, 0, false, true);

        // Show notification.
        AZStd::string notificationMessage;
        AzFramework::StringFunc::Path::GetFileName(filename.c_str(), notificationMessage);
        notificationMessage += " updated";
        GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_SUCCESS, notificationMessage.c_str());
    }


    bool FileManager::RelocateToAssetSourceFolder(AZStd::string& filename)
    {
        if (IsFileInAssetCache(filename))
        {
            const AZStd::string& assetCacheFolder = EMotionFX::GetEMotionFX().GetAssetCacheFolder();

            // Get the relative to asset cache filename.
            AZStd::string relativeFilename = filename.c_str();
            EMotionFX::GetEMotionFX().GetFilenameRelativeTo(&relativeFilename, assetCacheFolder.c_str());

            bool found;
            EBUS_EVENT_RESULT(found, AzToolsFramework::AssetSystemRequestBus, GetFullSourcePathFromRelativeProductPath, relativeFilename.c_str(), filename);
            return found;
        }
        return true;
    }


    void FileManager::RelocateToAssetCacheFolder(AZStd::string& filename)
    {
        if (IsFileInAssetSource(filename))
        {
            const AZStd::string& assetSourceFolder = EMotionFX::GetEMotionFX().GetAssetSourceFolder();
            const AZStd::string& assetCacheFolder = EMotionFX::GetEMotionFX().GetAssetCacheFolder();

            // Get the relative to asset cache filename.
            AZStd::string relativeFilename = filename.c_str();
            EMotionFX::GetEMotionFX().GetFilenameRelativeTo(&relativeFilename, assetSourceFolder.c_str());

            // Auto-relocate to the asset source folder.
            filename = assetCacheFolder + relativeFilename.c_str();
        }
    }


    bool FileManager::IsFileInAssetCache(const AZStd::string& filename) const
    {
        AZStd::string folderPath;
        AzFramework::StringFunc::Path::GetFullPath(filename.c_str(), folderPath);

        AZStd::string assetCacheFolder = EMotionFX::GetEMotionFX().GetAssetCacheFolder();
        
        // TODO: Using the incorrect path normalization here, so that the slashes get converted to the wrong ones. Why? Because elsewise IsASubFolderOfB() doesn't work.
        AzFramework::StringFunc::Path::Normalize(folderPath);
        AzFramework::StringFunc::Path::Normalize(assetCacheFolder);

        // TODO: Use the case sensitive version here. Can't do that yet as the folder path returned for an alias returns wrong capitalization while the one from the file dialog from Qt is correct. But as they differ, the function can't detect subfolders correctly.
        if (AzFramework::StringFunc::Equal(folderPath.c_str(), assetCacheFolder.c_str(), false) || AzFramework::StringFunc::Path::IsASubFolderOfB(folderPath.c_str(), assetCacheFolder.c_str()))
        {
            return true;
        }

        return false;
    }


    bool FileManager::IsFileInAssetSource(const AZStd::string& filename) const
    {
        AZStd::string folderPath;
        AzFramework::StringFunc::Path::GetFullPath(filename.c_str(), folderPath);

        AZStd::string assetSourceFolder = EMotionFX::GetEMotionFX().GetAssetSourceFolder();

        // TODO: Using the incorrect path normalization here, so that the slashes get converted to the wrong ones. Why? Because elsewise IsASubFolderOfB() doesn't work.
        AzFramework::StringFunc::Path::Normalize(folderPath);
        AzFramework::StringFunc::Path::Normalize(assetSourceFolder);

        // TODO: Use the case sensitive version here. Can't do that yet as the folder path returned for an alias returns wrong capitalization while the one from the file dialog from Qt is correct. But as they differ, the function can't detect subfolders correctly.
        if (AzFramework::StringFunc::Equal(folderPath.c_str(), assetSourceFolder.c_str(), false) || AzFramework::StringFunc::Path::IsASubFolderOfB(folderPath.c_str(), assetSourceFolder.c_str()))
        {
            return true;
        }

        return false;
    }


    void FileManager::UpdateLastUsedFolder(const char* filename, QString& outLastFolder) const
    {
        // Update the default location for the load and save dialogs.
        AZStd::string folderPath;
        AzFramework::StringFunc::Path::GetFullPath(filename, folderPath);

        // Only update the last used folder in case a valid folder path got extracted from the filename.
        // When canceling the file dialog, an empty filename will be passed to this function, the path extraction will fail.
        // Don't update the last used folder in this case.
        if (!folderPath.empty())
        {
            outLastFolder = folderPath.c_str();
        }
    }


    QString FileManager::GetLastUsedFolder(const QString& lastUsedFolder) const
    {
        // In case we didn't open up the file dialog yet, default to the asset source folder.
        if (lastUsedFolder.isEmpty())
        {
            const AZStd::string& assetSourceFolder = EMotionFX::GetEMotionFX().GetAssetSourceFolder();
            if (!assetSourceFolder.empty())
            {
                return assetSourceFolder.c_str();
            }
        }

        return lastUsedFolder;
    }


    AZStd::vector<AZStd::string> FileManager::SelectProductsOfType(AZ::Data::AssetType assetType, bool multiSelect) const
    {
        AZStd::vector<AZStd::string> filenames;
        AzToolsFramework::AssetBrowser::AssetSelectionModel selection = AzToolsFramework::AssetBrowser::AssetSelectionModel::AssetTypeSelection(assetType);
        selection.SetMultiselect(multiSelect);

        AzToolsFramework::EditorRequests::Bus::Broadcast(&AzToolsFramework::EditorRequests::BrowseForAssets, selection);
        if (selection.IsValid())
        {
            AZStd::string filename;
            const AZStd::vector<const AzToolsFramework::AssetBrowser::AssetBrowserEntry*>& products = selection.GetResults();
            for (const AzToolsFramework::AssetBrowser::AssetBrowserEntry* assetBrowserEntry : products)
            {
                const ProductAssetBrowserEntry* product = azrtti_cast<const ProductAssetBrowserEntry*>(assetBrowserEntry);

                filename.clear();
                AZStd::string cachePath = AZ::IO::FileIOBase::GetInstance()->GetAlias("@assets@");
                AzFramework::StringFunc::AssetDatabasePath::Normalize(cachePath);
                AzFramework::StringFunc::AssetDatabasePath::Join(cachePath.c_str(), product->GetRelativePath().c_str(), filename, true);

                filenames.push_back(filename.c_str());
            }
        }

        return filenames;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZStd::string FileManager::LoadActorFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        AZStd::vector<AZStd::string> filenames = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::ActorAsset>(), false);
        GetManager()->SetAvoidRendering(false);
        if (filenames.empty())
        {
            return AZStd::string();
        }
     
        return filenames[0];
    }


    AZStd::vector<AZStd::string> FileManager::LoadActorsFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        auto result = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::ActorAsset>(), true);
        GetManager()->SetAvoidRendering(false);
        return result;
    }


    AZStd::string FileManager::SaveActorFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        const AZStd::string filename = QFileDialog::getSaveFileName(parent,                                 // parent
																	tr("Save"),                                 // caption
                                                                    GetLastUsedFolder(mLastActorFolder),    // directory
																	tr("EMotion FX Actor Files (*.actor)"),
                                                                    &selectedFilter,
                                                                    options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        UpdateLastUsedFolder(filename.c_str(), mLastActorFolder);

        return filename;
    }


    void FileManager::SaveActor(EMotionFX::Actor* actor)
    {
        const AZStd::string command = AZStd::string::format("SaveActorAssetInfo -actorID %i", actor->GetID());

        AZStd::string result;
        if (EMStudio::GetCommandManager()->ExecuteCommand(command, result))
        {
            GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_SUCCESS, 
				tr("Actor <font color=green>successfully</font> saved"));
        }
        else
        {
            GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_ERROR, 
                AZStd::string::format("Actor <font color=red>failed</font> to save<br/><br/>%s", result.c_str()).c_str());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZStd::string FileManager::LoadWorkspaceFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        AZStd::string filename = QFileDialog::getOpenFileName(parent,                                                   // parent
															  tr("Open"),                                                   // caption
                                                              GetLastUsedFolder(mLastWorkspaceFolder),                  // directory
														      tr("EMotionFX Editor Workspace Files (*.emfxworkspace);;All Files (*)"),
                                                              &selectedFilter,
                                                              options).toUtf8().data();

        UpdateLastUsedFolder(filename.c_str(), mLastWorkspaceFolder);
        GetManager()->SetAvoidRendering(false);
        return filename;
    }


    AZStd::string FileManager::SaveWorkspaceFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        AZStd::string filename = QFileDialog::getSaveFileName(parent,
															  tr("Save"),                                       // caption
                                                              GetLastUsedFolder(mLastWorkspaceFolder),      // directory
															  tr("EMotionFX Editor Workspace Files (*.emfxworkspace)"),
                                                              &selectedFilter,
                                                              options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        if (IsFileInAssetCache(filename))
        {
            QMessageBox::critical(GetMainWindow(), tr("Error"), tr("Saving workspace in the asset cache folder is not allowed. Please select a different location."), QMessageBox::Ok);
            return AZStd::string();
        }

        UpdateLastUsedFolder(filename.c_str(), mLastWorkspaceFolder);
        return filename;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void FileManager::SaveMotion(AZ::u32 motionId)
    {
        const AZStd::string command = AZStd::string::format("SaveMotionAssetInfo -motionID %d", motionId);

        AZStd::string result;
        if (EMStudio::GetCommandManager()->ExecuteCommand(command, result))
        {
            GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_SUCCESS,
				tr("Motion <font color=green>successfully</font> saved"));
        }
        else
        {
            GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_ERROR,
                AZStd::string::format("Motion <font color=red>failed</font> to save<br/><br/>%s", result.c_str()).c_str());
        }
    }

    AZStd::string FileManager::LoadMotionFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        AZStd::vector<AZStd::string> filenames = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::MotionAsset>(), false);
        GetManager()->SetAvoidRendering(false);
        if (filenames.empty())
        {
            return AZStd::string();
        }

        return filenames[0];
    }


    AZStd::vector<AZStd::string> FileManager::LoadMotionsFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        auto result = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::MotionAsset>(), true);
        GetManager()->SetAvoidRendering(false);
        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZStd::string FileManager::LoadMotionSetFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        AZStd::vector<AZStd::string> filenames = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::MotionSetAsset>(), false);
        GetManager()->SetAvoidRendering(false);
        if (filenames.empty())
        {
            return AZStd::string();
        }

        return filenames[0];
    }


    AZStd::string FileManager::SaveMotionSetFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        AZStd::string filename = QFileDialog::getSaveFileName(parent,                                       // parent
			tr("Save"),                                       // caption
                                                              GetLastUsedFolder(mLastMotionSetFolder),      // directory
				tr("EMotion FX Motion Set Files (*.motionset)"),
                                                              &selectedFilter,
                                                              options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        UpdateLastUsedFolder(filename.c_str(), mLastMotionSetFolder);

        return filename;
    }


    void FileManager::SaveMotionSet(const char* filename, EMotionFX::MotionSet* motionSet, MCore::CommandGroup* commandGroup)
    {
        const AZStd::string command = AZStd::string::format("SaveMotionSet -motionSetID %i -filename \"%s\"", motionSet->GetID(), filename);

        if (commandGroup == nullptr)
        {
            AZStd::string result;
            if (GetCommandManager()->ExecuteCommand(command, result) == false)
            {
                GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_ERROR, 
                    AZStd::string::format("MotionSet <font color=red>failed</font> to save<br/><br/>%s", result.c_str()).c_str());
            }
            else
            {
                GetNotificationWindowManager()->CreateNotificationWindow(NotificationWindow::TYPE_SUCCESS, 
					tr("MotionSet <font color=green>successfully</font> saved"));
            }
        }
        else
        {
            commandGroup->AddCommandString(command);
        }
    }


    void FileManager::SaveMotionSet(QWidget* parent, EMotionFX::MotionSet* motionSet, MCore::CommandGroup* commandGroup)
    {
        AZStd::string filename = motionSet->GetFilename();

        if (filename.empty())
        {
            filename = SaveMotionSetFileDialog(parent);
            if (filename.empty())
            {
                // In case we canceled the file save dialog the filename will be empty, so we'll also cancel the save operation.
                return;
            }
        }

        SaveMotionSet(filename.c_str(), motionSet, commandGroup);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    AZStd::string FileManager::LoadAnimGraphFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);
        AZStd::vector<AZStd::string> filenames = SelectProductsOfType(azrtti_typeid<EMotionFX::Integration::AnimGraphAsset>(), false);
        GetManager()->SetAvoidRendering(false);
        if (filenames.empty())
        {
            return AZStd::string();
        }
        
        return filenames[0];
    }


    AZStd::string FileManager::SaveAnimGraphFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        AZStd::string filename = QFileDialog::getSaveFileName(parent,                                                   // parent
			tr("Save"),                                                   // caption
                                                              GetLastUsedFolder(mLastAnimGraphFolder),                 // directory
				tr("EMotion FX Anim Graph Files (*.animgraph);;All Files (*)"),
                                                              &selectedFilter,
                                                              options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        UpdateLastUsedFolder(filename.c_str(), mLastAnimGraphFolder);

        return filename;
    }


    // load a node map file
    AZStd::string FileManager::LoadNodeMapFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        const AZStd::string filename = QFileDialog::getOpenFileName(parent,                                         // parent
			tr("Open"),                                         // caption
                                                                    GetLastUsedFolder(mLastNodeMapFolder),          // directory
				tr("Node Map Files (*.nodeMap);;All Files (*)"),
                                                                    &selectedFilter,
                                                                    options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        UpdateLastUsedFolder(filename.c_str(), mLastNodeMapFolder);
        return filename;
    }


    // save a node map file
    AZStd::string FileManager::SaveNodeMapFileDialog(QWidget* parent)
    {
        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        const AZStd::string filename = QFileDialog::getSaveFileName(parent,                                         // parent
			tr("Save"),                                         // caption
                                                                    GetLastUsedFolder(mLastNodeMapFolder),          // directory
				tr("Node Map Files (*.nodeMap);;All Files (*)"),
                                                                    &selectedFilter,
                                                                    options).toUtf8().data();

        GetManager()->SetAvoidRendering(false);

        UpdateLastUsedFolder(filename.c_str(), mLastNodeMapFolder);
        return filename;
    }


    AZStd::string FileManager::LoadControllerPresetFileDialog(QWidget* parent, const char* defaultFolder)
    {
        AZStd::string dir;
        if (defaultFolder)
        {
            dir = defaultFolder;
        }
        else
        {
            dir = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        }

        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        QString filenameString = QFileDialog::getOpenFileName(parent,                                           // parent
			tr("Load"),                                           // caption
                                                              dir.c_str(),                                     // directory
				tr("EMotion FX Config Files (*.cfg);;All Files (*)"),
                                                              &selectedFilter,
                                                              options);

        GetManager()->SetAvoidRendering(false);

        AZStd::string filename;
        FromQtString(filenameString, &filename);

        return filename;
    }


    AZStd::string FileManager::SaveControllerPresetFileDialog(QWidget* parent, const char* defaultFolder)
    {
        AZStd::string dir;
        if (defaultFolder)
        {
            dir = defaultFolder;
        }
        else
        {
            dir = EMotionFX::GetEMotionFX().GetAssetSourceFolder().c_str();
        }

        GetManager()->SetAvoidRendering(true);

        QFileDialog::Options options;
        QString selectedFilter;
        QString filename = QFileDialog::getSaveFileName(parent,                                                 // parent
			tr("Save"),                                                 // caption
                                                        dir.c_str(),                                           // directory
				tr("EMotion FX Blend Config Files (*.cfg);;All Files (*)"),
                                                        &selectedFilter,
                                                        options);

        GetManager()->SetAvoidRendering(false);

        return FromQtString(filename);
    }
} // namespace EMStudio

#include <EMotionFX/Tools/EMotionStudio/EMStudioSDK/Source/FileManager.moc>