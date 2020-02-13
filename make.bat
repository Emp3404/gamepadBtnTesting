@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64"
mkdir build
pushd build
cl -Zi /EHsc "..\src\main.cpp" Xinput.lib Xinput9_1_0.lib
popd
