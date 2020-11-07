#!/bin/bash


mkdir 3rdparty
cd 3rdparty
git clone https://github.com/google/googletest
cd ..
mkdir build
cd build
cmake -E env GOOGLE_TEST_DIR=googletest cmake -DCMAKE_BUILD_TYPE=Debug cmake ..
make
make coverage
cp -r coverage ../
cd ..
rm -rf build
./bin/TestExe