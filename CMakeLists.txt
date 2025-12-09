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
    src/style/*
    src/data/haarcascades/*
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

# activate automoc to compile code from moc and set startup project for visual studio
set_target_properties(ExpressionDetector PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    VS_STARTUP_PROJECT ExpressionDetector
)

# force Visual Studio to launch binary from directory it is located
set_property(TARGET ExpressionDetector
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ExpressionDetector>"
)

# Define path to windeployqt
set(WINDEPLOYQT_EXECUTABLE "C:/Qt/6.10.0/msvc2022_64/bin/windeployqt.exe")

# Ajouter une commande post-build
add_custom_command(TARGET ExpressionDetector POST_BUILD
    COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:ExpressionDetector>"
    COMMENT "Running windeployqt to copy Qt DLLs..."
)

# add post build command to copy resources to binary folder
add_custom_command(TARGET ExpressionDetector POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/data/haarcascades
            $<TARGET_FILE_DIR:ExpressionDetector>/data/haarcascades
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/style
            $<TARGET_FILE_DIR:ExpressionDetector>/style
)

# installation of the solution
# install binary
install(TARGETS ExpressionDetector
    RUNTIME DESTINATION bin
)

# install resources
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/src/style
    DESTINATION bin
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/src/data/haarcascades
    DESTINATION bin/data
)

# deploy qt to package folder
install(SCRIPT "${CMAKE_SOURCE_DIR}/cmake/DeployQt.cmake")