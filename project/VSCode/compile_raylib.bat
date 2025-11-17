@echo off
echo Compiling %1...
C:\raylib\w64devkit\bin\gcc.exe -fdiagnostics-color=always -g -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -IC:\raylib\raylib\src -IC:\raylib\raylib\src\external %1 -o %~n1.exe -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm
if %ERRORLEVEL% == 0 (
    echo Compilation successful! Created %~n1.exe
) else (
    echo Compilation failed!
)
pause
