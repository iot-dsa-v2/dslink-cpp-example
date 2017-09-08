#!/bin/sh

if [ ! -d build ]; then
	mkdir build
fi

cmake . -B./build 
cd build
make
cd ..

echo "\n\nExecute the example"
build/src/requester
