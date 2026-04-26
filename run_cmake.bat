call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -G Ninja -B build-ninja -DCMAKE_MAKE_PROGRAM="C:\dev\Qt\qt-6.11\Tools\Ninja\ninja.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
