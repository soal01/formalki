#!/bin/bash


mkdir 3rdparty
cd 3rdparty
git clone https://github.com/google/googletest
cd ..
mkdir build
cd build
cmake -E env GOOGLE_TEST_DIR=googletest cmake ..
make
cd ..
rm -rf build
