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

#include "ResetSettingsDialog.h"

#include <EMotionFX/Source/Actor.h>
#include <EMotionFX/Source/ActorManager.h>
#include <EMotionFX/Source/AnimGraphManager.h>
#include <EMotionFX/Source/AnimGraph.h>
#include <EMotionFX/Source/EMotionFXManager.h>
#include <EMotionFX/Source/MotionManager.h>
#include <EMotionFX/Source/Motion.h>
#include <EMotionFX/Source/MotionSet.h>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace EMStudio
{
    // Iterates through the objects in one of the Manager classes, and returns
    // true if there is at least one object that is not owned by the runtime
    template<class ManagerType, typename GetNumFunc, typename GetEntityFunc>
    bool HasEntityInEditor(const ManagerType& manager, const GetNumFunc& getNumEntitiesFunc, const GetEntityFunc& getEntityFunc)
    {
        const uint32 numEntities = (manager.*getNumEntitiesFunc)();
        for (uint32 i = 0; i < numEntities; ++i)
        {
            const auto& entity = (manager.*getEntityFunc)(i);
            if (!entity->GetIsOwnedByRuntime())
            {
                return true;
            }
        }
        return false;
    }

    ResetSettingsDialog::ResetSettingsDialog(QWidget* parent)
        : QDialog(parent)
    {
        // update title of the dialog
        setWindowTitle(tr("Reset Workspace"));

        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->setAlignment(Qt::AlignTop);

        setObjectName("StyledWidgetDark");

        QLabel* topLabel = new QLabel(tr("<b>Select one or more items that you want to reset:</b>"));
        topLabel->setStyleSheet("background-color: rgb(40, 40, 40); padding: 6px;");
        topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        vLayout->addWidget(topLabel);
        vLayout->setMargin(0);

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setMargin(5);
        layout->setSpacing(4);
        vLayout->addLayout(layout);

        m_actorCheckbox = new QCheckBox("Actors");
        const bool hasActors = HasEntityInEditor(
            EMotionFX::GetActorManager(), &EMotionFX::ActorManager::GetNumActors, &EMotionFX::ActorManager::GetActor);
        m_actorCheckbox->setChecked(hasActors);
        m_actorCheckbox->setDisabled(!hasActors);

        m_motionCheckbox = new QCheckBox(tr("Motions"));
        const bool hasMotions = HasEntityInEditor(
            EMotionFX::GetMotionManager(), &EMotionFX::MotionManager::GetNumMotions, &EMotionFX::MotionManager::GetMotion);
        m_motionCheckbox->setChecked(hasMotions);
        m_motionCheckbox->setDisabled(!hasMotions);

        m_motionSetCheckbox = new QCheckBox(tr("Motion Sets"));
        const bool hasMotionSets = HasEntityInEditor(
            EMotionFX::GetMotionManager(), &EMotionFX::MotionManager::GetNumMotionSets, &EMotionFX::MotionManager::GetMotionSet);
        m_motionSetCheckbox->setChecked(hasMotionSets);
        m_motionSetCheckbox->setDisabled(!hasMotionSets);

        m_animGraphCheckbox = new QCheckBox(tr("Anim Graphs"));
        const bool hasAnimGraphs = HasEntityInEditor(
            EMotionFX::GetAnimGraphManager(), &EMotionFX::AnimGraphManager::GetNumAnimGraphs, &EMotionFX::AnimGraphManager::GetAnimGraph);
        m_animGraphCheckbox->setChecked(hasAnimGraphs);
        m_animGraphCheckbox->setDisabled(!hasAnimGraphs);

        layout->addWidget(m_actorCheckbox);
        layout->addWidget(m_motionCheckbox);
        layout->addWidget(m_motionSetCheckbox);
        layout->addWidget(m_animGraphCheckbox);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        vLayout->addWidget(buttonBox);
    }

    bool ResetSettingsDialog::IsActorsChecked() const
    {
        return m_actorCheckbox->isChecked();
    }

    bool ResetSettingsDialog::IsMotionsChecked() const
    {
        return m_motionCheckbox->isChecked();
    }

    bool ResetSettingsDialog::IsMotionSetsChecked() const
    {
        return m_motionSetCheckbox->isChecked();
    }

    bool ResetSettingsDialog::IsAnimGraphsChecked() const
    {
        return m_animGraphCheckbox->isChecked();
    }

} // namespace EMStudio

#include <EMotionFX/Tools/EMotionStudio/EMStudioSDK/Source/ResetSettingsDialog.moc>
