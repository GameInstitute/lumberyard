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
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#include "StdAfx.h"
#include "TrackViewKeyPropertiesDlg.h"
#include "TrackViewDialog.h"
#include "TrackViewSequence.h"
#include "TrackViewTrack.h"
#include "Controls/ReflectedPropertyControl/ReflectedPropertyCtrl.h"
#include <Maestro/Types/SequenceType.h>
#include <Maestro/Types/AnimValueType.h>

#include <ISplines.h>
#include <QVBoxLayout>
#include <QMessageBox>
#include <TrackView/ui_TrackViewTrackPropsDlg.h>

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyUIControls::OnInternalVariableChange(IVariable* var)
{
    CTrackViewSequence* sequence = GetIEditor()->GetAnimation()->GetSequence();
    AZ_Assert(sequence, "Expected valid sequence.");
    if (sequence)
    {
        CTrackViewKeyBundle keys = sequence->GetSelectedKeys();
        OnUIChange(var, keys);
    }
}

//////////////////////////////////////////////////////////////////////////
CTrackViewKeyPropertiesDlg::CTrackViewKeyPropertiesDlg(QWidget* hParentWnd)
    : QWidget(hParentWnd)
    , m_pLastTrackSelected(nullptr)
    , m_sequence(nullptr)
{
    QVBoxLayout* l = new QVBoxLayout();
    l->setMargin(0);
    m_wndTrackProps = new CTrackViewTrackPropsDlg(this);
    l->addWidget(m_wndTrackProps);
    m_wndProps = new ReflectedPropertyControl(this);
    m_wndProps->Setup(true, 120);
    m_wndProps->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    l->addWidget(m_wndProps);

    m_wndProps->SetStoreUndoByItems(false);

    setLayout(l);

    m_pVarBlock = new CVarBlock;

    // Add key UI classes
    std::vector<IClassDesc*> classes;
    GetIEditor()->GetClassFactory()->GetClassesByCategory("TrackViewKeyUI", classes);  // BySystemID(ESYSTEM_CLASS_TRACKVIEW_KEYUI, classes);
    for (IClassDesc* iclass : classes)
    {
        if (QObject* pObj = iclass->CreateQObject())
        {
            auto keyControl = qobject_cast<CTrackViewKeyUIControls*>(pObj);
            Q_ASSERT(keyControl);
            m_keyControls.push_back(keyControl);
        }
    }

    // Sort key controls by descending priority
    std::stable_sort(m_keyControls.begin(), m_keyControls.end(),
        [](const _smart_ptr<CTrackViewKeyUIControls>& a, const _smart_ptr<CTrackViewKeyUIControls>& b)
        {
            return a->GetPriority() > b->GetPriority();
        }
        );

    CreateAllVars();
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::OnVarChange(IVariable* pVar)
{
    // If it was a motion that just changed, we need to rebuild the controls
    // so the min/max on the sliders update correctly.
    if (m_sequence && pVar->GetDataType() == IVariable::DT_MOTION)
    {
        OnKeySelectionChanged(m_sequence);
    }
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::CreateAllVars()
{
    for (int i = 0; i < (int)m_keyControls.size(); i++)
    {
        m_keyControls[i]->SetKeyPropertiesDlg(this);
        m_keyControls[i]->OnCreateVars();
    }
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::PopulateVariables()
{
    //SetVarBlock( m_pVarBlock,functor(*this,&CTrackViewKeyPropertiesDlg::OnVarChange) );

    // Must first clear any selection in properties window.
    m_wndProps->RemoveAllItems();
    m_wndProps->AddVarBlock(m_pVarBlock);

    m_wndProps->SetUpdateCallback(functor(*this, &CTrackViewKeyPropertiesDlg::OnVarChange));
    //m_wndProps->m_props.ExpandAll();


    ReloadValues();
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::PopulateVariables(ReflectedPropertyControl* propCtrl)
{
    propCtrl->RemoveAllItems();
    propCtrl->AddVarBlock(m_pVarBlock);

    propCtrl->ReloadValues();
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::OnKeysChanged(CTrackViewSequence* pSequence)
{
    CTrackViewKeyBundle selectedKeys = pSequence->GetSelectedKeys();

    if (selectedKeys.GetKeyCount() > 0 && selectedKeys.AreAllKeysOfSameType())
    {
        CTrackViewTrack* pTrack = selectedKeys.GetKey(0).GetTrack();

        CAnimParamType paramType = pTrack->GetParameterType();
        EAnimCurveType trackType = pTrack->GetCurveType();
        AnimValueType valueType = pTrack->GetValueType();

        for (int i = 0; i < (int)m_keyControls.size(); i++)
        {
            if (m_keyControls[i]->SupportTrackType(paramType, trackType, valueType))
            {
                m_keyControls[i]->OnKeySelectionChange(selectedKeys);
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::OnKeySelectionChanged(CTrackViewSequence* sequence)
{
    m_sequence = sequence;

    if (nullptr == sequence)
    {
        m_wndProps->ClearSelection();
        m_pVarBlock->DeleteAllVariables();
        m_wndProps->setEnabled(false);
        m_wndTrackProps->setEnabled(false);
        return;
    }

    CTrackViewKeyBundle selectedKeys = sequence->GetSelectedKeys();

    m_wndTrackProps->OnKeySelectionChange(selectedKeys);

    bool bSelectChangedInSameTrack
        = m_pLastTrackSelected
            && selectedKeys.GetKeyCount() == 1
            && selectedKeys.GetKey(0).GetTrack() == m_pLastTrackSelected;

    // Every Key in an Asset Blend track can have different min/max values on the float sliders
    // because it's based on the duration of the motion that is set. So don't try to 
    // reuse the controls when the selection changes, otherwise the tooltips may be wrong.
    bool reuseControls = bSelectChangedInSameTrack && m_pLastTrackSelected && (m_pLastTrackSelected->GetValueType() != AnimValueType::AssetBlend);

    if (selectedKeys.GetKeyCount() == 1)
    {
        m_pLastTrackSelected = selectedKeys.GetKey(0).GetTrack();
    }
    else
    {
        m_pLastTrackSelected = nullptr;
    }

    if (reuseControls)
    {
        m_wndProps->ClearSelection();
    }
    else
    {
        m_pVarBlock->DeleteAllVariables();
    }

    m_wndProps->setEnabled(false);
    m_wndTrackProps->setEnabled(false);
    bool bAssigned = false;
    if (selectedKeys.GetKeyCount() > 0 && selectedKeys.AreAllKeysOfSameType())
    {
        CTrackViewTrack* pTrack = selectedKeys.GetKey(0).GetTrack();

        CAnimParamType paramType = pTrack->GetParameterType();
        EAnimCurveType trackType = pTrack->GetCurveType();
        AnimValueType valueType = pTrack->GetValueType();

        for (int i = 0; i < (int)m_keyControls.size(); i++)
        {
            if (m_keyControls[i]->SupportTrackType(paramType, trackType, valueType))
            {
                if (!reuseControls)
                {
                    AddVars(m_keyControls[i]);
                }

                if (m_keyControls[i]->OnKeySelectionChange(selectedKeys))
                {
                    bAssigned = true;
                }

                break;
            }
        }

        m_wndProps->setEnabled(true);
        m_wndTrackProps->setEnabled(true);
    }
    else
    {
        m_wndProps->setEnabled(false);
        m_wndTrackProps->setEnabled(false);
    }

    if (reuseControls)
    {
        ReloadValues();
    }
    else
    {
        PopulateVariables();
    }
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::AddVars(CTrackViewKeyUIControls* pUI)
{
    CVarBlock* pVB = pUI->GetVarBlock();
    for (int i = 0, num = pVB->GetNumVariables(); i < num; i++)
    {
        IVariable* pVar = pVB->GetVariable(i);
        m_pVarBlock->AddVariable(pVar);
    }
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewKeyPropertiesDlg::ReloadValues()
{
    m_wndProps->ReloadValues();
}

void CTrackViewKeyPropertiesDlg::OnSequenceChanged(CTrackViewSequence* sequence)
{
    OnKeySelectionChanged(sequence);
    m_wndTrackProps->OnSequenceChanged();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CTrackViewTrackPropsDlg::CTrackViewTrackPropsDlg(QWidget* parent /* = 0 */)
    : QWidget(parent)
    , ui(new Ui::CTrackViewTrackPropsDlg)
{
    ui->setupUi(this);

    // Use editingFinished and a custom signal stepByFinished (and not valueChanged)
    // so the time will be updated when the user finishes editing the time field (hits enter)
    // or if the arrow keys (or mouse click on the arrow buttons) in the spinner box are
    // pressed. Don't just use valueChanged because we don't want intermediate values
    // like 1 as the user is typing 10 to register as updates to the key values. Keys
    // are identified by time, so the keys jumping around like that can stomp existing keys
    // that happen to live at the intermediate values.
    connect(ui->TIME, SIGNAL(editingFinished()), this, SLOT(OnUpdateTime()));
    connect(ui->TIME, SIGNAL(stepByFinished()), this, SLOT(OnUpdateTime()));
}

CTrackViewTrackPropsDlg::~CTrackViewTrackPropsDlg()
{
}

//////////////////////////////////////////////////////////////////////////
void CTrackViewTrackPropsDlg::OnSequenceChanged()
{
    CTrackViewSequence* pSequence = GetIEditor()->GetAnimation()->GetSequence();

    if (pSequence)
    {
        Range range = pSequence->GetTimeRange();
        ui->TIME->setRange(range.start, range.end);
    }
}


//////////////////////////////////////////////////////////////////////////
bool CTrackViewTrackPropsDlg::OnKeySelectionChange(CTrackViewKeyBundle& selectedKeys)
{
    m_keyHandle = CTrackViewKeyHandle();

    if (selectedKeys.GetKeyCount() == 1)
    {
        m_keyHandle = selectedKeys.GetKey(0);
    }

    if (m_keyHandle.IsValid())
    {
        // Block the callback, the values is already set in m_keyHandle.GetTime(), no need to
        // reset it and create an undo even like the user was setting it via the UI.
        ui->TIME->blockSignals(true);
        ui->TIME->setValue(m_keyHandle.GetTime());
        ui->TIME->blockSignals(false);
        ui->PREVNEXT->setText(QString::number(m_keyHandle.GetIndex() + 1));

        ui->PREVNEXT->setEnabled(true);
        ui->TIME->setEnabled(true);
    }
    else
    {
        ui->PREVNEXT->setEnabled(FALSE);
        ui->TIME->setEnabled(FALSE);
    }
    return true;
}

void CTrackViewTrackPropsDlg::OnUpdateTime()
{
    if (!m_keyHandle.IsValid())
    {
        return;
    }

    const float time = (float)ui->TIME->value();

    // Check if the sequence is legacy
    CTrackViewTrack* track = m_keyHandle.GetTrack();
    if (nullptr != track)
    {
        CTrackViewSequence* sequence = track->GetSequence();
        if (nullptr != sequence && !AZ::IsClose(m_keyHandle.GetTime(), time, AZ::g_fltEps))
        {
            bool isDuringUndo = false;
            AzToolsFramework::ToolsApplicationRequests::Bus::BroadcastResult(isDuringUndo, &AzToolsFramework::ToolsApplicationRequests::Bus::Events::IsDuringUndoRedo);

            if (isDuringUndo)
            {
                m_keyHandle.SetTime(time);
            }
            else
            {
                // Let the AZ Undo system manage the nodes on the sequence entity
                AzToolsFramework::ScopedUndoBatch undoBatch("Change key time");

                CTrackViewKeyHandle existingKey = track->GetKeyByTime(time);

                // If there is an existing key at this time, remove it so the 
                // new key at this time is the only one here.
                if (existingKey.IsValid())
                {
                    // Save the old time before we set the new time so we
                    // can reselect the m_keyHandle after the Delete. 
                    float currentTime = m_keyHandle.GetTime();

                    // There is a bug in QT where editingFinished will get fired a second time if we show a QMessageBox
                    // so work around it by blocking signal before we do it.
                    ui->TIME->blockSignals(true);

                    QString msgBody = tr("There is an existing key at the specified time. If you continue, the existing key will be removed.");
                    if (QMessageBox::warning(this, tr("Overwrite Existing Key?"), msgBody, QMessageBox::Cancel | QMessageBox::Yes) == QMessageBox::Cancel)
                    {
                        // Restore the old value and return.
                        ui->TIME->setValue(currentTime);
                        ui->TIME->blockSignals(false);
                        return;
                    }
                    else
                    {
                        ui->TIME->blockSignals(false);
                    }

                    // Delete the key that is able to get replaced. This will
                    // cause a sort and may cause m_keyHandle to become invalid.
                    existingKey.Delete();

                    // Reselect the key handle by time.
                    m_keyHandle = track->GetKeyByTime(currentTime);
                }

                m_keyHandle.SetTime(time);

                undoBatch.MarkEntityDirty(sequence->GetSequenceComponentEntityId());
            }
        }
    }
}

#include <TrackView/TrackViewKeyPropertiesDlg.moc>