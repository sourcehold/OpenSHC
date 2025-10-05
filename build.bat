taskkill /f /t /im mspdbsrv.exe

del build-%1
mkdir build-%1

pushd build-%1
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=%1
nmake

popd


