start "main1" "%~dp0\main.exe"
ping 127.0.0.1 -n 3 > nul
start "main2" "%~dp0\main.exe"
ping 127.0.0.1 -n 3 > nul
start "main3" "%~dp0\main.exe"

