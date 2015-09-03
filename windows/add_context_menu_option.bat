@echo off
REM Add "Share via cutehttpd" to context menu, run as administrator

REM Check Administrator permissions
net session >nul 2>&1
if %errorLevel% == 0 (
  reg add "HKEY_CLASSES_ROOT\Directory\shell\Share via cutehttpd\command" /t REG_SZ /d "%~dp0\cutehttpd.exe %%1"
  reg add "HKEY_CLASSES_ROOT\Directory\Background\shell\Share via cutehttpd\command" /t REG_SZ /d "%~dp0\cutehttpd.exe %%V"
  echo Success. Context menu entry added.
) else (
  echo Error. Run this bat with Administrator permissions.
)
pause
