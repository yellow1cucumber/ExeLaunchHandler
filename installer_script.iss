[Setup]
AppName=ExeLaunchHandler
AppVersion=1.0
DefaultDirName={pf}\ExeLaunchHandler
DefaultGroupName=ExeLaunchHandler
UninstallDisplayIcon={app}\ExeLaunchHandler.exe
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
DisableProgramGroupPage=yes

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Files]
; === Основной EXE ===
Source: "out\release-32\ExeLaunchHandler.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.exe"; DestDir: "{app}"; Check: Is64BitInstallMode

; === Конфиг ===
Source: "out\release-32\config.json"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-64\config.json"; DestDir: "{app}"; Check: Is64BitInstallMode

; === DLL и PYD (64-bit) ===
Source: "out\release-64\ExeLaunchHandler.Config.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.Constants.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.Launch.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.Logging.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.Pipes.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.PyPipeBridge.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.ResultsAPI.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\ExeLaunchHandler.UI.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\pipebridge.cp310-win_amd64.pyd"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\python310.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\python310.zip"; DestDir: "{app}"; Check: Is64BitInstallMode

; === DLL и PYD (32-bit) ===
Source: "out\release-32\ExeLaunchHandler.Config.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.Constants.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.Launch.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.Logging.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.Pipes.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.PyPipeBridge.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.ResultsAPI.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\ExeLaunchHandler.UI.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\pipebridge.cp310-win32.pyd"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\python310.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\python310.zip"; DestDir: "{app}"; Check: not Is64BitInstallMode


; === Qt DLL (64-bit) ===
Source: "out\release-64\Qt5Core.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\Qt5Gui.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\Qt5Widgets.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\Qt5Svg.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\d3dcompiler_47.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\libEGL.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\libGLESV2.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "out\release-64\opengl32sw.dll"; DestDir: "{app}"; Check: Is64BitInstallMode

; === Qt DLL (32-bit) ===
Source: "out\release-32\Qt5Core.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\Qt5Gui.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\Qt5Widgets.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\Qt5Svg.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\d3dcompiler_47.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\libEGL.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\libGLESV2.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "out\release-32\opengl32sw.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode

; === VC++ Redist ===
Source: "out\release-64\vc_redist.x64.exe"; DestDir: "{tmp}"; Flags: dontcopy; Check: Is64BitInstallMode
Source: "out\release-32\vc_redist.x86.exe"; DestDir: "{tmp}"; Flags: dontcopy; Check: not Is64BitInstallMode

; === Qt Плагины (64-bit) ===
Source: "out\release-64\platforms\*"; DestDir: "{app}\platforms"; Flags: recursesubdirs createallsubdirs; Check: Is64BitInstallMode
Source: "out\release-64\imageformats\*"; DestDir: "{app}\imageformats"; Flags: recursesubdirs createallsubdirs; Check: Is64BitInstallMode
Source: "out\release-64\iconengines\*"; DestDir: "{app}\iconengines"; Flags: recursesubdirs createallsubdirs; Check: Is64BitInstallMode
Source: "out\release-64\styles\*"; DestDir: "{app}\styles"; Flags: recursesubdirs createallsubdirs; Check: Is64BitInstallMode

; === Qt Плагины (32-bit) ===
Source: "out\release-32\platforms\*"; DestDir: "{app}\platforms"; Flags: recursesubdirs createallsubdirs; Check: not Is64BitInstallMode
Source: "out\release-32\imageformats\*"; DestDir: "{app}\imageformats"; Flags: recursesubdirs createallsubdirs; Check: not Is64BitInstallMode
Source: "out\release-32\iconengines\*"; DestDir: "{app}\iconengines"; Flags: recursesubdirs createallsubdirs; Check: not Is64BitInstallMode
Source: "out\release-32\styles\*"; DestDir: "{app}\styles"; Flags: recursesubdirs createallsubdirs; Check: not Is64BitInstallMode

; === Ресурсы ===
Source: "resources\splash.png"; DestDir: "{app}\resources"

[Icons]
Name: "{app}\Run UI.lnk"; Filename: "{app}\ExeLaunchHandler.exe"; Parameters: "-c config.json --ui"; WorkingDir: "{app}"; IconFilename: "{app}\ExeLaunchHandler.exe"
Name: "{app}\Run CLI.lnk"; Filename: "{app}\ExeLaunchHandler.exe"; Parameters: "-c config.json"; WorkingDir: "{app}"; IconFilename: "{app}\ExeLaunchHandler.exe"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"
