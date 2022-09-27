MD build
cd .\build
MD mvs19
cd .\mvs19
MD Debug
MD Release
cd ..\
cd ..\
copy ".\include\freeglut\freeglut.dll" ".\build\mvs19\Debug\freeglut.dll"
copy ".\include\glew\glew32.dll" ".\build\mvs19\Debug\glew32.dll"
copy ".\include\freeglut\freeglut.dll" ".\build\mvs19\Release\freeglut.dll"
copy ".\include\glew\glew32.dll" ".\build\mvs19\Release\glew32.dll"
copy ".\include\freeglut\freeglut.lib" ".\build\mvs19\freeglut.lib"
copy ".\include\glew\glew32.lib" ".\build\mvs19\glew32.lib"
copy ".\include\SOIL\x64\soil.lib" ".\build\mvs19\soil.lib"
cd .\build
cd .\mvs19
cmake ..\..\ -G "Visual Studio 16 2019" -A x64 -T v142 -DCMAKE_CONFIGURATION_TYPES="Release;Debug;" -DCMAKE_GENERATOR_PLATFORM=x64 -DPLATFORM=WINDOWS
cd ..\..\