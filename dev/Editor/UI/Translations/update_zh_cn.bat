@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)
echo "Update Sandbox"
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Editor   										-ts 	.\zh_cn\Sandbox.ts

echo "Update Framework"
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Framework\AzQtComponents 								-ts 	.\zh_cn\Framework\AzQtComponents.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Framework\AzToolsFramework 							-ts 	.\zh_cn\Framework\AzToolsFramework.ts

echo "Update Gems"
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\CloudGemDynamicContent 							    -ts 	.\zh_cn\Gems\CloudGemDynamicContent.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\EMotionFX 								            -ts 	.\zh_cn\Gems\EMotionFX.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\GraphCanvas 								            -ts 	.\zh_cn\Gems\GraphCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\ImageProcessing 								        -ts 	.\zh_cn\Gems\ImageProcessing.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\ScriptCanvas 								            -ts 	.\zh_cn\Gems\ScriptCanvas.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\SliceFavorites 								        -ts 	.\zh_cn\Gems\SliceFavorites.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Gems\Substance 								            -ts 	.\zh_cn\Gems\Substance.ts

echo "Update Plugins" 
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ComponentEntityEditorPlugin 			-ts 	.\zh_cn\Plugins\ComponentEntityEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\CryDesigner 			                -ts 	.\zh_cn\Plugins\CryDesigner.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\DeploymentTool                        -ts 	.\zh_cn\Plugins\DeploymentTool.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorAssetImporter 			        -ts 	.\zh_cn\Plugins\EditorAssetImporter.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorAudioControlsEditor 			-ts 	.\zh_cn\Plugins\EditorAudioControlsEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorCommon 			                -ts 	.\zh_cn\Plugins\EditorCommon.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorUI_QT 			                -ts 	.\zh_cn\Plugins\EditorUI_QT.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\FBXPlugin 			                -ts 	.\zh_cn\Plugins\FBXPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\MaglevControlPanel 			        -ts 	.\zh_cn\Plugins\MaglevControlPanel.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ParticleEditorPlugin 			        -ts 	.\zh_cn\Plugins\ParticleEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\PerforcePlugin 			            -ts 	.\zh_cn\Plugins\PerforcePlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\ProjectSettingsTool 			        -ts 	.\zh_cn\Plugins\ProjectSettingsTool.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\UiCanvasEditor 			            -ts 	.\zh_cn\Plugins\UiCanvasEditor.ts