@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)

echo "Release Sandbox"
%QTDIR%\lrelease .\zh_cn\Sandbox.ts

echo "Release Framework"
%QTDIR%\lrelease .\zh_cn\AzQtComponents.ts
%QTDIR%\lrelease .\zh_cn\AzToolsFramework.ts
echo "Release Plugins" 
%QTDIR%\lrelease .\zh_cn\ComponentEntityEditorPlugin.ts
%QTDIR%\lrelease .\zh_cn\CryDesigner.ts
%QTDIR%\lrelease .\zh_cn\DeploymentTool.ts
%QTDIR%\lrelease .\zh_cn\EditorAssetImporter.ts
%QTDIR%\lrelease .\zh_cn\EditorAudioControlsEditor.ts
%QTDIR%\lrelease .\zh_cn\EditorCommon.ts
%QTDIR%\lrelease .\zh_cn\EditorUI_QT.ts
%QTDIR%\lrelease .\zh_cn\FBXPlugin.ts
%QTDIR%\lrelease .\zh_cn\MaglevControlPanel.ts
%QTDIR%\lrelease .\zh_cn\ParticleEditorPlugin.ts
%QTDIR%\lrelease .\zh_cn\PerforcePlugin.ts
%QTDIR%\lrelease .\zh_cn\UiCanvasEditor.ts

echo "Release Gems"
%QTDIR%\lrelease .\zh_cn\CloudGemDynamicContent.ts
%QTDIR%\lrelease .\zh_cn\EMotionFX.ts
%QTDIR%\lrelease .\zh_cn\GraphCanvas.ts
%QTDIR%\lrelease .\zh_cn\ScriptCanvas.ts
%QTDIR%\lrelease .\zh_cn\ScriptCanvasDeveloper.ts
%QTDIR%\lrelease .\zh_cn\Substance.ts
