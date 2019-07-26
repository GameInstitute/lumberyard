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

#include <Editor/PropertyWidgets/ActorMorphTargetHandler.h>
#include <Editor/PropertyWidgets/ActorGoalNodeHandler.h>
#include <Editor/PropertyWidgets/ActorJointHandler.h>
#include <Editor/PropertyWidgets/AnimGraphNodeHandler.h>
#include <Editor/PropertyWidgets/AnimGraphNodeNameHandler.h>
#include <Editor/PropertyWidgets/AnimGraphParameterHandler.h>
#include <Editor/PropertyWidgets/AnimGraphTagHandler.h>
#include <Editor/PropertyWidgets/AnimGraphTransitionHandler.h>
#include <Editor/PropertyWidgets/AnimGraphParameterHandler.h>
#include <Editor/PropertyWidgets/AnimGraphParameterMaskHandler.h>
#include <Editor/PropertyWidgets/BlendSpaceEvaluatorHandler.h>
#include <Editor/PropertyWidgets/BlendSpaceMotionContainerHandler.h>
#include <Editor/PropertyWidgets/BlendSpaceMotionHandler.h>
#include <Editor/PropertyWidgets/EventDataHandler.h>
#include <Editor/PropertyWidgets/MotionSetMotionIdHandler.h>
#include <Editor/PropertyWidgets/BlendTreeRotationLimitHandler.h>
#include <Editor/PropertyWidgets/MotionSetNameHandler.h>
#include <Editor/PropertyWidgets/RagdollJointHandler.h>
#include <Editor/PropertyWidgets/TransitionStateFilterLocalHandler.h>
#include <Editor/PropertyWidgets/BlendNParamWeightsHandler.h>
#include <Editor/PropertyWidgets/LODTreeSelectionHandler.h>
#include <AzToolsFramework/UI/PropertyEditor/PropertyEditorAPI.h>


namespace EMotionFX
{
    AZStd::vector<AzToolsFramework::PropertyHandlerBase*> RegisterPropertyTypes()
    {
#if defined(EMOTIONFXANIMATION_EDITOR)
        AZStd::vector<AzToolsFramework::PropertyHandlerBase*> propertyHandlers =
        {
            aznew EMotionFX::ActorJointElementHandler(),
            aznew EMotionFX::ActorSingleJointHandler(),
            aznew EMotionFX::ActorMultiJointHandler(),
            aznew EMotionFX::ActorMultiWeightedJointHandler(),
            aznew EMotionFX::ActorSingleMorphTargetHandler(),
            aznew EMotionFX::ActorMultiMorphTargetHandler(),
            aznew EMotionFX::ActorGoalNodeHandler(),
            aznew EMotionFX::AnimGraphNodeIdHandler(),
            aznew EMotionFX::AnimGraphNodeNameHandler(),
            aznew EMotionFX::AnimGraphMotionNodeIdHandler(),
            aznew EMotionFX::AnimGraphSingleParameterHandler(),
            aznew EMotionFX::AnimGraphMultipleParameterHandler(),
            aznew EMotionFX::AnimGraphParameterMaskHandler(),
            aznew EMotionFX::AnimGraphStateIdHandler(),
            aznew EMotionFX::AnimGraphTagHandler(),
            aznew EMotionFX::AnimGraphMultiTransitionIdHandler(),
            aznew EMotionFX::BlendSpaceEvaluatorHandler(),
            aznew EMotionFX::BlendSpaceMotionContainerHandler(),
            aznew EMotionFX::BlendSpaceMotionHandler(),
            aznew EMotionFX::EventDataHandler(),
            aznew EMotionFX::RagdollMultiJointHandler(),
            aznew EMotionFX::TransitionStateFilterLocalHandler(),
            aznew EMotionFX::MotionSetMultiMotionIdHandler(),
            aznew EMotionFX::MotionIdRandomSelectionWeightsHandler(),
            aznew EMotionFX::MotionSetNameHandler(),
            aznew EMotionFX::BlendTreeRotationLimitHandler(),
            aznew EMotionFX::BlendTreeRotationLimitContainerHandler(),
            aznew EMotionFX::Pipeline::UI::LODTreeSelectionHandler(),
            aznew EMotionFX::BlendNParamWeightsHandler(),
            aznew EMotionFX::BlendNParamWeightElementHandler()
        };

        for (const auto handler : propertyHandlers)
        {
            AzToolsFramework::PropertyTypeRegistrationMessages::Bus::Broadcast(&AzToolsFramework::PropertyTypeRegistrationMessages::RegisterPropertyType, handler);
        }
        return propertyHandlers;
#endif
        return AZStd::vector<AzToolsFramework::PropertyHandlerBase*> {};
    }


    void UnregisterPropertyTypes(const AZStd::vector<AzToolsFramework::PropertyHandlerBase*>& handlers)
    {
#if defined(EMOTIONFXANIMATION_EDITOR)
        for (auto handler : handlers)
        {
            if (!handler->AutoDelete())
            {
                AzToolsFramework::PropertyTypeRegistrationMessages::Bus::Broadcast(&AzToolsFramework::PropertyTypeRegistrationMessages::UnregisterPropertyType, handler);
                delete handler;
            }
        }
#endif
    }
} // namespace EMotionFX
