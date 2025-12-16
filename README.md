# Expression Detector
This repository contains source code for a facial expression recognition application. There are three modes available :
- a simple display of camera output.
- Face detection : draw a rectangle on areas containing faces.
- Expression detection (currently not implemented) : draw a rectangle on areas containing faces and display the expression read on faces.

## Prerequisites
This project is written with C++ and required Qt 6.10.0 and Opencv 4.12.

## Build
You can easily build this project using CMake as a CMakeLists file is provided in this repository. I recommend using a build folder for cmake build files, and specify OpenCV and Qt install directories with cmake cahe entry argument (-D) in cmake command like the following one :
```
cmake -S . -B build -G "Visual Studio 17 2022" -DQT_DIRECTORY:STRING=C:/Qt/6.10.0 -DOPENCV_DIRECTORY:STRING=D:/opencv -A x64
```

Command to generate Release binary : 
```
cmake --build build --config Release
```

The project can be installed using cmake command (the result will be shipped in the package folder) :
```
cmake --install build --prefix ./package
```

This solution use windeployqt utility to automatically deploy Qt libraries after build and for package installation.
