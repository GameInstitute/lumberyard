@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)

echo "Release Sandbox"
%QTDIR%\lrelease .\Sandbox_zh-cn.ts

echo "Release Framework"
%QTDIR%\lrelease .\AzQtComponents_zh-cn.ts
%QTDIR%\lrelease .\AzToolsFramework_zh-cn.ts
echo "Release Plugins" 
%QTDIR%\lrelease .\ComponentEntityEditorPlugin_zh-cn.ts
%QTDIR%\lrelease .\CryDesigner_zh-cn.ts
%QTDIR%\lrelease .\DeploymentTool_zh-cn.ts
%QTDIR%\lrelease .\EditorAssetImporter_zh-cn.ts
%QTDIR%\lrelease .\EditorAudioControlsEditor_zh-cn.ts
%QTDIR%\lrelease .\EditorCommon_zh-cn.ts
%QTDIR%\lrelease .\EditorUI_QT_zh-cn.ts
%QTDIR%\lrelease .\FBXPlugin_zh-cn.ts
%QTDIR%\lrelease .\MaglevControlPanel_zh-cn.ts
%QTDIR%\lrelease .\ParticleEditorPlugin_zh-cn.ts
%QTDIR%\lrelease .\PerforcePlugin_zh-cn.ts
%QTDIR%\lrelease .\UiCanvasEditor_zh-cn.ts

echo "Release Gems"
%QTDIR%\lrelease .\CloudGemDynamicContent_zh-cn.ts
%QTDIR%\lrelease .\EMotionFX_zh-cn.ts
%QTDIR%\lrelease .\GraphCanvas_zh-cn.ts
%QTDIR%\lrelease .\ScriptCanvas_zh-cn.ts
%QTDIR%\lrelease .\ScriptCanvasDeveloper_zh-cn.ts
%QTDIR%\lrelease .\Substance_zh-cn.ts
