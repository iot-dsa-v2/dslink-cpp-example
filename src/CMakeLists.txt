find_package(Boost 1.6 REQUIRED COMPONENTS system thread date_time)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${TEST_LIBS} ${Boost_LIBRARIES})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
set(LIBS ${LIBS} ${OPENSSL_LIBRARIES})

# sdk-dslink-cpp setup
set(DSA_SDK_ROOT "../deps/sdk-dslink-cpp")
set(DSA_SDK_NAME "${CMAKE_STATIC_LIBRARY_PREFIX}dsa_sdk${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(DSA_SDK_LIBRARIES "${DSA_SDK_ROOT}/lib/${DSA_SDK_NAME}")
list(APPEND DSA_SDK_INCLUDE_DIRS
            "${DSA_SDK_ROOT}/include"
            "${DSA_SDK_ROOT}/include/dsa/internal")

foreach (dir  ${DSA_SDK_INCLUDE_DIRS})
  include_directories(${dir})
endforeach ()

# Requester
set(LIBS ${DSA_SDK_LIBRARIES} ${LIBS})
set(TARGET_NAME "requester")
set(SOURCES "requester.cc")

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} ${LIBS})
