@IF %QTDIR% ==  (
    echo QTDIR environment variable is not set!
    EXIT B 1
)

echo Release Sandbox
%QTDIR%lrelease .\zh_cn\Sandbox.ts

echo Release Framework
%QTDIR%lrelease .\zh_cn\Framework\AzQtComponents.ts
%QTDIR%lrelease .\zh_cn\Framework\AzToolsFramework.ts

echo Release Plugins 
%QTDIR%lrelease .\zh_cn\Plugins\ComponentEntityEditorPlugin.ts
%QTDIR%lrelease .\zh_cn\Plugins\CryDesigner.ts
%QTDIR%lrelease .\zh_cn\Plugins\DeploymentTool.ts
%QTDIR%lrelease .\zh_cn\Plugins\EditorAssetImporter.ts
%QTDIR%lrelease .\zh_cn\Plugins\EditorAudioControlsEditor.ts
%QTDIR%lrelease .\zh_cn\Plugins\EditorCommon.ts
%QTDIR%lrelease .\zh_cn\Plugins\EditorUI_QT.ts
%QTDIR%lrelease .\zh_cn\Plugins\FBXPlugin.ts
%QTDIR%lrelease .\zh_cn\Plugins\MaglevControlPanel.ts
%QTDIR%lrelease .\zh_cn\Plugins\ParticleEditorPlugin.ts
%QTDIR%lrelease .\zh_cn\Plugins\PerforcePlugin.ts
%QTDIR%lrelease .\zh_cn\Plugins\ProjectSettingsTool.ts
%QTDIR%lrelease .\zh_cn\Plugins\UiCanvasEditor.ts

echo Release Gems
%QTDIR%lrelease .\zh_cn\Gems\CloudGemDynamicContent.ts
%QTDIR%lrelease .\zh_cn\Gems\EMotionFX.ts
%QTDIR%lrelease .\zh_cn\Gems\GraphCanvas.ts
%QTDIR%lrelease .\zh_cn\Gems\ImageProcessing.ts
%QTDIR%lrelease .\zh_cn\Gems\ScriptCanvas.ts
%QTDIR%lrelease .\zh_cn\Gems\SliceFavorites.ts
%QTDIR%lrelease .\zh_cn\Gems\Substance.ts