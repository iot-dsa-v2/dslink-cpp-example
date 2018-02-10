cmake_minimum_required(VERSION 3.6.2)
project(dslink-cpp-example)

# add sources
set(SOURCES example_main.cc)

set(DSA_SDK_SOURCE ${SDK_PROJECT_SOURCE_DIR}/src)
set(DSA_SDK_INCLUDE ${SDK_PROJECT_SOURCE_DIR}/include)
set(DSA_SDK_DEPS ${SDK_PROJECT_SOURCE_DIR}/deps)

include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
include_directories(${DSA_SDK_INCLUDE})
include_directories(${DSA_SDK_DEPS}/msgpack/include)
include_directories(${DSA_SDK_DEPS}/jansson-build/include)
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${DSA_SDK_SOURCE}/sdk")
include_directories("${DSA_SDK_INCLUDE}")

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} ${DSA_SDK_LIBRARY})
target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
target_link_libraries(${TARGET_NAME} ${OPENSSL_LIBRARIES})
if (UNIX)
    target_link_libraries(${TARGET_NAME} dl pthread)
endif ()

if (NOT PREBUILT_SDK_PATH)
    add_dependencies(${TARGET_NAME} ${DSA_SDK_LIBRARY})
endif ()