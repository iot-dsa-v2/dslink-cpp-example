cmake_minimum_required(VERSION 3.6.2)

set(TARGET_NAME example_dslink)

# uncomment and write if you want to use prebuilt sdk
set (PREBUILT_SDK_PATH ${PROJECT_BINARY_DIR}/deps/sdk-dslink-cpp)

if (PREBUILT_SDK_PATH)
    # you can change sourcepaths
    set(PREBUILT_SDK_SOURCE_PATH ${PROJECT_SOURCE_DIR}/deps/sdk-dslink-cpp)
    set(PREBUILT_SDK_BINARY_PATH ${PREBUILT_SDK_PATH})
endif ()

option(ENABLE_TEST "enable tests for dslink" ON)
if (ENABLE_TEST)
    set (DSA_INCLUDE_TEST ON)
endif ()

if (PREBUILT_SDK_SOURCE_PATH)
    set(DSA_SDK_SOURCE_DIR ${PREBUILT_SDK_SOURCE_PATH})
else ()
    set(DSA_SDK_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/sdk-dslink-cpp)
endif ()

#TODO: this path recognition should be improved
if (PREBUILT_SDK_BINARY_PATH)
    set(DSA_SDK_BINARY_DIR ${PREBUILT_SDK_BINARY_PATH})
    message(${DSA_SDK_BINARY_DIR})

    if (UNIX)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            find_library(DSA_SDK_LIBRARY dsa_sdk ${DSA_SDK_BINARY_DIR}/src/sdk)
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            find_library(DSA_SDK_LIBRARY dsa_sdk ${DSA_SDK_BINARY_DIR}/src/sdk)
        endif()
    endif(UNIX)

    if (WIN32)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            find_library(DSA_SDK_LIBRARY dsa_sdk ${DSA_SDK_BINARY_DIR}/src/sdk/Debug)
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            find_library(DSA_SDK_LIBRARY dsa_sdk ${DSA_SDK_BINARY_DIR}/src/sdk/Release)
        endif()
    endif (WIN32)

else ()
    set(DSA_SDK_BINARY_DIR ${PROJECT_BINARY_DIR}/deps/sdk-dslink-cpp)
    set(DSA_SDK_LIBRARY dsa_sdk)
endif ()

include(${DSA_SDK_SOURCE_DIR}/CMakeListsConfig.txt)

add_subdirectory("./src")

if (NOT PREBUILT_SDK_PATH)
    add_subdirectory(${DSA_SDK_SOURCE_DIR})
endif ()

if(ENABLE_TEST)
    add_subdirectory("./test")
endif()