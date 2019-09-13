@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)
echo "Update Sandbox"
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Editor   										-ts 	.\zh_cn\Sandbox.ts

echo "Update Framework"
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Framework\AzQtComponents 								-ts 	.\zh_cn\AzQtComponents.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Framework\AzToolsFramework 							-ts 	.\zh_cn\AzToolsFramework.ts

echo "Update Gems"
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\CloudGemDynamicContent 							    -ts 	.\zh_cn\CloudGemDynamicContent.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\EMotionFX 								            -ts 	.\zh_cn\EMotionFX.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\GraphCanvas 								            -ts 	.\zh_cn\GraphCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\ImageProcessing 								        -ts 	.\zh_cn\ImageProcessing.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\ScriptCanvas 								            -ts 	.\zh_cn\ScriptCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\SliceFavorites 								        -ts 	.\zh_cn\SliceFavorites.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\Substance 								            -ts 	.\zh_cn\Substance.ts

echo "Update Plugins" 
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ComponentEntityEditorPlugin 			-ts 	.\zh_cn\ComponentEntityEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\CryDesigner 			                -ts 	.\zh_cn\CryDesigner.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\DeploymentTool                        -ts 	.\zh_cn\DeploymentTool.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorAssetImporter 			        -ts 	.\zh_cn\EditorAssetImporter.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorAudioControlsEditor 			-ts 	.\zh_cn\EditorAudioControlsEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorCommon 			                -ts 	.\zh_cn\EditorCommon.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorUI_QT 			                -ts 	.\zh_cn\EditorUI_QT.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\FBXPlugin 			                -ts 	.\zh_cn\FBXPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\MaglevControlPanel 			        -ts 	.\zh_cn\MaglevControlPanel.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ParticleEditorPlugin 			        -ts 	.\zh_cn\ParticleEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\PerforcePlugin 			            -ts 	.\zh_cn\PerforcePlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ProjectSettingsTool 			        -ts 	.\zh_cn\ProjectSettingsTool.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\UiCanvasEditor 			            -ts 	.\zh_cn\UiCanvasEditor.ts