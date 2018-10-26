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

#include "MorphTargetSelectionWindow.h"
#include "EMStudioManager.h"
#include <QPushButton>
#include <QVBoxLayout>


namespace EMStudio
{
    MorphTargetSelectionWindow::MorphTargetSelectionWindow(QWidget* parent, bool multiSelect)
        : QDialog(parent)
    {
        setWindowTitle(QObject::tr("Morph target selection window"));

        QVBoxLayout* layout = new QVBoxLayout();

        mListWidget = new QListWidget();
        mListWidget->setAlternatingRowColors(true);
        if (multiSelect)
        {
            mListWidget->setSelectionMode(QListWidget::ExtendedSelection);
        }
        else
        {
            mListWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        }

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        mOKButton       = new QPushButton(QObject::tr("OK"));
		mCancelButton = new QPushButton(QObject::tr("Cancel"));
        buttonLayout->addWidget(mOKButton);
        buttonLayout->addWidget(mCancelButton);

        layout->addWidget(mListWidget);
        layout->addLayout(buttonLayout);
        setLayout(layout);

        connect(mOKButton, SIGNAL(clicked()), this, SLOT(accept()));
        connect(mCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
        connect(mListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnSelectionChanged()));
    }


    MorphTargetSelectionWindow::~MorphTargetSelectionWindow()
    {
    }


    const AZStd::vector<uint32>& MorphTargetSelectionWindow::GetMorphTargetIDs() const
    {
        return mSelection;
    }


    void MorphTargetSelectionWindow::OnSelectionChanged()
    {
        mSelection.clear();

        const int numItems = mListWidget->count();
        mSelection.reserve(numItems);
        for (int i = 0; i < numItems; ++i)
        {
            QListWidgetItem* item = mListWidget->item(i);
            if (!item->isSelected())
            {
                continue;
            }

            mSelection.emplace_back(item->data(Qt::UserRole).toInt());
        }
    }


    void MorphTargetSelectionWindow::Update(EMotionFX::MorphSetup* morphSetup, const AZStd::vector<uint32>& selection)
    {
        if (morphSetup == nullptr)
        {
            return;
        }

        mListWidget->blockSignals(true);
        mListWidget->clear();

        mSelection = selection;

        const uint32 numMorphTargets = morphSetup->GetNumMorphTargets();
        for (uint32 i = 0; i < numMorphTargets; ++i)
        {
            EMotionFX::MorphTarget* morphTarget = morphSetup->GetMorphTarget(i);
            const uint32 morphTargetID = morphTarget->GetID();

            QListWidgetItem* item = new QListWidgetItem();
            item->setText(morphTarget->GetName());
            item->setData(Qt::UserRole, morphTargetID);

            mListWidget->addItem(item);

            if (AZStd::find(mSelection.begin(), mSelection.end(), morphTargetID) != mSelection.end())
            {
                item->setSelected(true);
            }
        }

        mListWidget->blockSignals(false);
        mSelection = selection;
    }
} // namespace EMStudio

#include <EMotionFX/Tools/EMotionStudio/EMStudioSDK/Source/MorphTargetSelectionWindow.moc>