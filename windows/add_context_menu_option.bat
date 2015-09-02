REM Add "Share via cutehttpd" to context menu, run as administrator
reg add "HKEY_CLASSES_ROOT\Directory\shell\Share via cutehttpd\command" /t REG_SZ /d "%~dp0\cutehttpd.exe %%1"
reg add "HKEY_CLASSES_ROOT\Directory\Background\shell\Share via cutehttpd\command" /t REG_SZ /d "%~dp0\cutehttpd.exe %%V"
