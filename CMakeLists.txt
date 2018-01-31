cmake_minimum_required(VERSION 3.6.2)

set(TARGET_NAME example_dslink)

option(USE_PREBUILT_DSA_SDK "use headers and/or libraries from a prebuilt sdk path" OFF)

if (USE_PREBUILT_DSA_SDK)
    # write source path
    set(DSA_SDK_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/sdk-dslink-cpp)
    # write prebuilt sdk binary path
    set(DSA_SDK_BINARY_DIR ${PROJECT_BINARY_DIR}/deps/sdk-dslink-cpp)
    find_library(DSA_SDK_LIBRARY dsa_sdk ${DSA_SDK_BINARY_DIR}/src/sdk)
else ()
    set(DSA_SDK_BINARY_DIR ${PROJECT_BINARY_DIR}/deps/sdk-dslink-cpp)
    set(DSA_SDK_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/sdk-dslink-cpp)
    set(DSA_SDK_LIBRARY dsa_sdk)
endif ()

include(${DSA_SDK_SOURCE_DIR}/CMakeListsConfig.txt)

if (NOT USE_PREBUILT_DSA_SDK)
    add_subdirectory("${DSA_SDK_SOURCE_DIR}")
endif ()

add_subdirectory("./src")