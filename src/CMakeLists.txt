cmake_minimum_required(VERSION 3.6.2)
project(dslink-cpp-example)

# add sources
set(SOURCES example_main.cc)

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