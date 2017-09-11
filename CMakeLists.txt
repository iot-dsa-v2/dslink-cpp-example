cmake_minimum_required(VERSION 3.7)

if (UNIX)
        # Download sdk-dslink-cpp at configure time
        execute_process(COMMAND "./install.sh"
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/sdk-dslink-cpp)
        if (result)
            message(FATAL_ERROR "Build step for sdk-dslink-cpp failed: ${result}")
        endif ()
endif (UNIX)

if (WIN32)
        add_subdirectory("./deps/sdk-dslink-cpp")
endif (WIN32)

add_subdirectory("./src")
