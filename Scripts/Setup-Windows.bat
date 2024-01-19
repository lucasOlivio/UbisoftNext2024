@echo off

pushd ..
Extern\Binaries\Premake\Windows\premake5.exe --file=Build.lua vs2022
popd
pause