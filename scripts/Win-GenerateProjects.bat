pushd ..\
call vendor\bin\premake\premake5.exe vs2022
popd
pushd ..\Hazel\vendor\assimp\
cmake CMakeLists.txt 
cmake --build . --config Release
popd
mkdir ..\bin\Debug-windows-x86_64\Sandbox
mkdir ..\bin\Release-windows-x86_64\Sandbox
copy ..\Hazel\vendor\assimp\bin\Release\assimp-vc143-mt.dll ..\bin\Debug-windows-x86_64\Sandbox\
copy ..\Hazel\vendor\assimp\bin\Release\assimp-vc143-mt.dll ..\bin\Release-windows-x86_64\Sandbox\
echo "TODO: download the model files to Sandbox\assets\"
PAUSE