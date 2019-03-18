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

#pragma once

#include "EMotionFXConfig.h"
#include "AnimGraphNode.h"


namespace EMotionFX
{
    /**
     *
     */
    class EMFX_API BlendTreeSmoothingNode
        : public AnimGraphNode
    {
    public:
        AZ_RTTI(BlendTreeSmoothingNode, "{80D8C793-3CD4-4216-B804-CC00EAD20FAA}", AnimGraphNode)
        AZ_CLASS_ALLOCATOR_DECL

        enum
        {
            INPUTPORT_DEST              = 0,
            OUTPUTPORT_RESULT           = 0
        };

        enum
        {
            PORTID_INPUT_DEST           = 0,
            PORTID_OUTPUT_RESULT        = 0
        };

        class EMFX_API UniqueData
            : public AnimGraphNodeData
        {
            EMFX_ANIMGRAPHOBJECTDATA_IMPLEMENT_LOADSAVE
        public:
            AZ_CLASS_ALLOCATOR_DECL

            UniqueData(AnimGraphNode* node, AnimGraphInstance* animGraphInstance)
                : AnimGraphNodeData(node, animGraphInstance)     { mCurrentValue = 0.0f; mFrameDeltaTime = 0.0f; }

        public:
            float   mFrameDeltaTime;
            float   mCurrentValue;
        };

        BlendTreeSmoothingNode();
        ~BlendTreeSmoothingNode();

        bool InitAfterLoading(AnimGraph* animGraph) override;

        void Rewind(AnimGraphInstance* animGraphInstance) override;
        uint32 GetVisualColor() const override;
        bool GetSupportsDisable() const override;

        const char* GetPaletteName() const override;
        AnimGraphObject::ECategory GetPaletteCategory() const override;

        void OnUpdateUniqueData(AnimGraphInstance* animGraphInstance) override;

        void SetInterpolationSpeed(float interpolationSpeed);
        void SetStartVAlue(float startValue);
        void SetUseStartVAlue(bool useStartValue);

        static void Reflect(AZ::ReflectContext* context);

    private:
        void Update(AnimGraphInstance* animGraphInstance, float timePassedInSeconds) override;
        AZ::Crc32 GetStartValueVisibility() const;

        float               m_interpolationSpeed;
        float               m_startValue;
        bool                m_useStartValue;
        static const float  s_targetReachedRelativeTolerance;
    };
} // namespace EMotionFX