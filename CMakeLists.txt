cmake_minimum_required(VERSION 4.0)

# configure project
project(ExpressionDetector)
# set path to build repository, depending on build type (debug, release, etc)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# include qt library
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64/lib/cmake/Qt6" "D:/opencv/build/x64/vc16/lib")
find_package(
    Qt6
    REQUIRED COMPONENTS Widgets  Core Gui
)
link_directories(${Qt_LIBRARY_DIRS})
include_directories(${Qt_INCLUDE_DIRS})

# include opencv library
find_package(OpenCV REQUIRED)

# configure source files
file (
    GLOB_RECURSE
    source_files
    src/*.cpp
    src/*.hpp
    style/*
    data/haarcascades/*
)

# configure executable
add_executable (
    ExpressionDetector
    ${source_files}
)

# configure link
target_link_libraries(
    ExpressionDetector
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${OpenCV_LIBS}
)

target_include_directories(ExpressionDetector PRIVATE ${OpenCV_INCLUDE_DIRS})

# activate automoc to compile code from moc
set_target_properties(ExpressionDetector PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Define path to windeployqt
set(WINDEPLOYQT_EXECUTABLE "C:/Qt/6.10.0/msvc2022_64/bin/windeployqt.exe")

# Ajouter une commande post-build
add_custom_command(TARGET ExpressionDetector POST_BUILD
    COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:ExpressionDetector>"
    COMMENT "Running windeployqt to copy Qt DLLs..."
)

