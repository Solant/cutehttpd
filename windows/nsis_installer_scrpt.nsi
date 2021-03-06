;-----------
;Variables

!define APP_NAME "cutehttpd"
!define LICENSE_FILE "LICENSE.md"

;-----------
;Attributes

Name "${APP_NAME}"

;------
;Interface

!include "MUI2.nsh"
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${LICENSE_FILE}"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Outfile "cutehttpd_installer.exe"

InstallDir "$PROGRAMFILES\${APP_NAME}"

Section "install" Installation_info
    SetOutPath $INSTDIR
    File LICENSE.md
    File cutehttpd.exe
    WriteRegStr "HKCR" "Directory\shell\Share via cutehttpd\command" "" "$INSTDIR\cutehttpd.exe %1"
    WriteRegStr "HKCR" "Directory\Background\shell\Share via cutehttpd\command" "" "$INSTDIR\cutehttpd.exe"
    WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Uninstall"
  DeleteRegKey "HKCR" "Directory\Background\shell\Share via cutehttpd"
  DeleteRegKey "HKCR" "Directory\shell\Share via cutehttpd"
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\LICENSE.md"
  Delete "$INSTDIR\cutehttpd.exe"
SectionEnd
