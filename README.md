# dslink-cpp-example

1. run 'git clone --recursive https://github.com/iot-dsa-v2/dslink-cpp-example.git'
2. refer to 'https://github.com/iot-dsa-v2/sdk-dslink-cpp' for sdk-dslink-cpp setup

3. On Windows platform - Visual Studio 2017
   - in visual studio, use file-open-folder.. to open dslink-cpp-example project
   - use cmake-cache-generate to generate build files
   - use cmake-build only-deps/sdk-dslink-cpp/src/sdk/dsa_sdk.lib to build dsa_sdk.lib
   - build src/requester.exe

4. On Linux, run './install.sh'. This script builds 1) dsa_sdk library, 2) executable requester and 3) execute the requester
