pushd ..\
call vendor\bin\premake\premake5.exe vs2022
popd
pushd ..\Hazel\vendor\assimp\
cmake CMakeLists.txt 
cmake --build .
popd
copy ..\Hazel\vendor\assimp\bin\Debug\assimp-vc143-mtd.dll ..\bin\Debug-windows-x86_64\Sandbox\
copy ..\Hazel\vendor\assimp\bin\Debug\assimp-vc143-mtd.dll ..\bin\Release-windows-x86_64\Sandbox\
PAUSE