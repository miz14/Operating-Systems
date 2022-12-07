@echo off
(echo.set sh=CreateObject^("Wscript.Shell"^)
echo.sh.Run """%~nx0"" 1", 0)>launch.vbs
if "%~1"=="" (start "" "launch.vbs"&exit /b)
start Project7.exe
timeout /t 3
start Project7.exe
timeout /t 4
start Project7.exe