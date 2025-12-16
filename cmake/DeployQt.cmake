execute_process(
    COMMAND "C:/Qt/6.10.0/msvc2022_64/bin/windeployqt.exe"
            --release
            ${CMAKE_INSTALL_PREFIX}/bin/ExpressionDetector.exe
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
)
message(STATUS windeployqt result=${result})
message(STATUS windeployqt output=${output})
message(STATUS windeployqt error=${error})