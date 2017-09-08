cmake_minimum_required(VERSION 3.7)

# Download sdk-dslink-cpp at configure time
configure_file(CMakeLists.txt.in sdk-dslink-cpp-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/sdk-dslink-cpp-download)
if (result)
    message(FATAL_ERROR "CMake step for sdk-dslink-cpp failed: ${result}")
endif ()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/sdk-dslink-cpp-download)
if (result)
    message(FATAL_ERROR "Build step for sdk-dslink-cpp failed: ${result}")
endif ()

execute_process(COMMAND "./install.sh"
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/deps/sdk-dslink-cpp)
if (result)
    message(FATAL_ERROR "Additional build step for sdk-dslink-cpp failed: ${result}")
endif ()

add_subdirectory("./src")
