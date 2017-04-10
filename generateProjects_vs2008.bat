
call env.bat 9

mkdir win64
cd win64

cmake -G "Visual Studio 9 2008 Win64" ..
pause
start "" %MSVC_EXE% transport.sln
