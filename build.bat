@echo off

pushd build
cl /FC /Zi /EHsc /I C:\opencv\build\include ..\win32_main.cpp /link /LIBPATH "C:\opencv\build\x64\vc15\lib\opencv_world454.lib"
popd
