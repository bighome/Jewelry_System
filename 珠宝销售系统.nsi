; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "珠宝销售系统"
!define PRODUCT_VERSION "1.4"
!define PRODUCT_PUBLISHER "SMALLHOME, Inc."
!define PRODUCT_WEB_SITE "http://www.smallhome.asia"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Calcute.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "D:\workspace\jewelrySystem_JJ\jewelrySystem_JJ\Resources\ico.ico"
!define MUI_UNICON "D:\workspace\jewelrySystem_JJ\jewelrySystem_JJ\Resources\ico.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "D:\anzhuangxuzhi.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Calcute.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\doc\Mysql安装教程.pdf"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Welsh"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\珠宝销售系统"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "E:\我的文件夹\jewelryV1.4\Calcute.dat"
  File "E:\我的文件夹\jewelryV1.4\Calcute.exe"
  SetOutPath "$INSTDIR\codecs"
  File "E:\我的文件夹\jewelryV1.4\codecs\qcncodecs4.dll"
  File "E:\我的文件夹\jewelryV1.4\codecs\qjpcodecs4.dll"
  File "E:\我的文件夹\jewelryV1.4\codecs\qkrcodecs4.dll"
  File "E:\我的文件夹\jewelryV1.4\codecs\qtwcodecs4.dll"
  SetOutPath "$INSTDIR\database"
  File "E:\我的文件夹\jewelryV1.4\database\saleserver_last.sql"
  SetOutPath "$INSTDIR\doc"
  File "E:\我的文件夹\jewelryV1.4\doc\Mysql安装教程.pdf"
  File "E:\我的文件夹\jewelryV1.4\doc\mysql导入导出.sql文件.pdf"
  File "E:\我的文件夹\jewelryV1.4\doc\教程1.exe"
  File "E:\我的文件夹\jewelryV1.4\doc\教程2.exe"
  SetOutPath "$INSTDIR\imageformats"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qgif4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qico4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qjpeg4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qmng4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qsvg4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qtga4.dll"
  File "E:\我的文件夹\jewelryV1.4\imageformats\qtiff4.dll"
  SetOutPath "$INSTDIR\img"
  File "E:\我的文件夹\jewelryV1.4\img\ico.ico"
  SetOutPath "$INSTDIR"
  File "E:\我的文件夹\jewelryV1.4\jewelryDatabaseLayer.dll"
  File "E:\我的文件夹\jewelryV1.4\jewelrySystem_JJ.exe"
  CreateDirectory "$SMPROGRAMS\珠宝销售系统"
  CreateShortCut "$SMPROGRAMS\珠宝销售系统\珠宝销售系统.lnk" "$INSTDIR\jewelrySystem_JJ.exe"
  CreateShortCut "$DESKTOP\珠宝销售系统.lnk" "$INSTDIR\jewelrySystem_JJ.exe"
  File "E:\我的文件夹\jewelryV1.4\libmysql.dll"
  File "E:\我的文件夹\jewelryV1.4\Microsoft.VC90.CRT.manifest"
  File "E:\我的文件夹\jewelryV1.4\msvcm90.dll"
  File "E:\我的文件夹\jewelryV1.4\msvcp90.dll"
  File "E:\我的文件夹\jewelryV1.4\msvcr90.dll"
  File "E:\我的文件夹\jewelryV1.4\printfsettings.ini"
  File "E:\我的文件夹\jewelryV1.4\QtCore4.dll"
  File "E:\我的文件夹\jewelryV1.4\QtGui4.dll"
  File "E:\我的文件夹\jewelryV1.4\QtNetwork4.dll"
  File "E:\我的文件夹\jewelryV1.4\QtSql4.dll"
  File "E:\我的文件夹\jewelryV1.4\QtSvg4.dll"
  File "E:\我的文件夹\jewelryV1.4\QtTest4.dll"
  File "E:\我的文件夹\jewelryV1.4\Safari.ico"
  File "E:\我的文件夹\jewelryV1.4\Setup.exe"
  File "E:\我的文件夹\jewelryV1.4\seversettings.ini"
  SetOutPath "$INSTDIR\sqldrivers"
  File "E:\我的文件夹\jewelryV1.4\sqldrivers\qsqlite4.dll"
  File "E:\我的文件夹\jewelryV1.4\sqldrivers\qsqlmysql4.dll"
  File "E:\我的文件夹\jewelryV1.4\sqldrivers\qsqlodbc4.dll"
  File "E:\我的文件夹\jewelryV1.4\sqldrivers\qsqlpsql4.dll"
  SetOutPath "$INSTDIR"
  File "E:\我的文件夹\jewelryV1.4\Untitled03.nsi"
  File "E:\我的文件夹\jewelryV1.4\updateSystem.exe"
  File "E:\我的文件夹\jewelryV1.4\workarea.txt"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\珠宝销售系统\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\珠宝销售系统\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Calcute.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Calcute.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，其及所有的组件？" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\workarea.txt"
  Delete "$INSTDIR\updateSystem.exe"
  Delete "$INSTDIR\Untitled03.nsi"
  Delete "$INSTDIR\sqldrivers\qsqlpsql4.dll"
  Delete "$INSTDIR\sqldrivers\qsqlodbc4.dll"
  Delete "$INSTDIR\sqldrivers\qsqlmysql4.dll"
  Delete "$INSTDIR\sqldrivers\qsqlite4.dll"
  Delete "$INSTDIR\seversettings.ini"
  Delete "$INSTDIR\Setup.exe"
  Delete "$INSTDIR\Safari.ico"
  Delete "$INSTDIR\QtTest4.dll"
  Delete "$INSTDIR\QtSvg4.dll"
  Delete "$INSTDIR\QtSql4.dll"
  Delete "$INSTDIR\QtNetwork4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\printfsettings.ini"
  Delete "$INSTDIR\msvcr90.dll"
  Delete "$INSTDIR\msvcp90.dll"
  Delete "$INSTDIR\msvcm90.dll"
  Delete "$INSTDIR\Microsoft.VC90.CRT.manifest"
  Delete "$INSTDIR\libmysql.dll"
  Delete "$INSTDIR\jewelrySystem_JJ.exe"
  Delete "$INSTDIR\jewelryDatabaseLayer.dll"
  Delete "$INSTDIR\img\ico.ico"
  Delete "$INSTDIR\imageformats\qtiff4.dll"
  Delete "$INSTDIR\imageformats\qtga4.dll"
  Delete "$INSTDIR\imageformats\qsvg4.dll"
  Delete "$INSTDIR\imageformats\qmng4.dll"
  Delete "$INSTDIR\imageformats\qjpeg4.dll"
  Delete "$INSTDIR\imageformats\qico4.dll"
  Delete "$INSTDIR\imageformats\qgif4.dll"
  Delete "$INSTDIR\doc\教程2.exe"
  Delete "$INSTDIR\doc\教程1.exe"
  Delete "$INSTDIR\doc\mysql导入导出.sql文件.pdf"
  Delete "$INSTDIR\doc\Mysql安装教程.pdf"
  Delete "$INSTDIR\database\saleserver_last.sql"
  Delete "$INSTDIR\codecs\qtwcodecs4.dll"
  Delete "$INSTDIR\codecs\qkrcodecs4.dll"
  Delete "$INSTDIR\codecs\qjpcodecs4.dll"
  Delete "$INSTDIR\codecs\qcncodecs4.dll"
  Delete "$INSTDIR\Calcute.exe"
  Delete "$INSTDIR\Calcute.dat"

  Delete "$SMPROGRAMS\珠宝销售系统\Uninstall.lnk"
  Delete "$SMPROGRAMS\珠宝销售系统\Website.lnk"
  Delete "$DESKTOP\珠宝销售系统.lnk"
  Delete "$SMPROGRAMS\珠宝销售系统\珠宝销售系统.lnk"

  RMDir "$SMPROGRAMS\珠宝销售系统"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR\img"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR\doc"
  RMDir "$INSTDIR\database"
  RMDir "$INSTDIR\codecs"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd