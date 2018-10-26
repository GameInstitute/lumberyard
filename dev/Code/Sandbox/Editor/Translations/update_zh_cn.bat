@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)
echo "Update Sandbox"
%QTDIR%\lupdate -noobsolete ..\..\Editor   										-ts 	.\zh_cn\Sandbox.ts


echo "Update Framework"
%QTDIR%\lupdate -noobsolete ..\..\..\Framework\AzQtComponents 					-ts 	.\zh_cn\AzQtComponents.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Framework\AzToolsFramework 				-ts 	.\zh_cn\AzToolsFramework.ts

echo "Update Plugins" 
%QTDIR%\lupdate -noobsolete ..\..\Plugins\ComponentEntityEditorPlugin 			-ts 	.\zh_cn\ComponentEntityEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\CryDesigner 							-ts 	.\zh_cn\CryDesigner.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\DeploymentTool 						-ts 	.\zh_cn\DeploymentTool.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorAssetImporter 					-ts 	.\zh_cn\EditorAssetImporter.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorAudioControlsEditor				-ts 	.\zh_cn\EditorAudioControlsEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorCommon 							-ts 	.\zh_cn\EditorCommon.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorUI_QT 							-ts 	.\zh_cn\EditorUI_QT.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\FBXPlugin								-ts 	.\zh_cn\FBXPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\MaglevControlPanel 					-ts 	.\zh_cn\MaglevControlPanel.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\ParticleEditorPlugin 					-ts 	.\zh_cn\ParticleEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\PerforcePlugin 						-ts 	.\zh_cn\PerforcePlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\UiCanvasEditor 						-ts 	.\zh_cn\UiCanvasEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorAnimation 						-ts 	.\zh_cn\EditorAnimation.ts
%QTDIR%\lupdate -noobsolete ..\..\Plugins\EditorModularBehaviorTree				-ts 	.\zh_cn\EditorModularBehaviorTree.ts

echo "Update Gems"
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\CloudGemDynamicContent 			-ts 	.\zh_cn\CloudGemDynamicContent.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\EMotionFX 							-ts 	.\zh_cn\EMotionFX.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\GraphCanvas 						-ts 	.\zh_cn\GraphCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\ScriptCanvas 						-ts 	.\zh_cn\ScriptCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\ScriptCanvasDeveloper 				-ts 	.\zh_cn\ScriptCanvasDeveloper.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\Substance 							-ts 	.\zh_cn\Substance.ts
%QTDIR%\lupdate -noobsolete ..\..\..\..\Gems\SceneProcessing 					-ts 	.\zh_cn\SceneProcessing.ts




