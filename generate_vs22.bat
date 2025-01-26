@echo off

if not exist "build" mkdir "build"

pushd build

cmake ../ -G "Visual Studio 17 2022"

popd

pause