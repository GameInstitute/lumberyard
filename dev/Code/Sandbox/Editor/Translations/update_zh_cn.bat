@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)
echo "Update Sandbox"
%QTDIR%\lupdate -noobsolete ..\..\Editor   -ts 	.\Sandbox_zh-cn.ts


echo "Update Framework"
%QTDIR%\lupdate -noobsolete ..\..\..\Framework\AzQtComponents 		-ts 	.\AzQtComponents_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Framework\AzToolsFramework 	-ts 	.\AzToolsFramework_zh-cn.ts

echo "Update Plugins" 
%QTDIR%\lupdate -noobsolete ..\..\Plugins\ComponentEntityEditorPlugin 			-ts 	.\ComponentEntityEditorPlugin_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\CryDesigner 							-ts 	.\CryDesigner_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\DeploymentTool 						-ts 	.\DeploymentTool_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorAssetImporter 					-ts 	.\EditorAssetImporter_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorAudioControlsEditor				-ts 	.\EditorAudioControlsEditor_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorCommon 							-ts 	.\EditorCommon_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorUI_QT 							-ts 	.\EditorUI_QT_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\FBXPlugin								-ts 	.\FBXPlugin_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\MaglevControlPanel 					-ts 	.\MaglevControlPanel_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\ParticleEditorPlugin 					-ts 	.\ParticleEditorPlugin_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\PerforcePlugin 						-ts 	.\PerforcePlugin_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\UiCanvasEditor 						-ts 	.\UiCanvasEditor_zh-cn.ts

echo "Update Gems"
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\CloudGemDynamicContent 	-ts 	.\CloudGemDynamicContent_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\EMotionFX 				-ts 	.\EMotionFX_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\GraphCanvas 				-ts 	.\GraphCanvas_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\ScriptCanvas 				-ts 	.\ScriptCanvas_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\ScriptCanvasDeveloper 	-ts 	.\ScriptCanvasDeveloper_zh-cn.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\Substance 				-ts 	.\Substance_zh-cn.ts





