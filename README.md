# Expression Detector
This repository contains source code for a facial expression recognition application. There are three modes available :
- a simple display of camera output.
- Face detection : draw a rectangle on areas containing faces.
- Expression detection (currently not implemented) : draw a rectangle on areas containing faces and display the expression read on faces.

## Prerequisites
This project is written with C++ and required Qt 6.10.0 and Opencv 4.12.

## Build
You can easily build this project using CMake. In order to do this, you must do the following :
- add Opencv and Qt paths to CMAKE_PREFIX_PATH (for example "C:/Qt/6.10.0/msvc2022_64/lib/cmake/Qt6" and "C:/opencv/build/x64/vc16/lib")
- set WINDEPLOYQT_EXECUTABLE variable to define path where to find windeployqt utility (used to automatically deploy Qt libraries after build). For example "C:/Qt/6.10.0/msvc2022_64/bin/windeployqt.exe"
