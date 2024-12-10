#!/bin/bash

if [ -e lib/libcjson.so ]; then
  echo "Nothing to be done"
  exit 0
fi

cmake --version
if [ $? -ne 0 ]; then
  echo "CMake is not installed"
  exit 1
fi

git --version
if [ $? -ne 0 ]; then
  echo "git is not installed"
  exit 1
fi

make --version
if [ $? -ne 0 ]; then
  echo "make is not installed"
  exit 1
fi

realpath --version
if [ $? -ne 0 ]; then
  echo "realpath is not installed"
  exit 1
fi

git clone --depth 1 https://github.com/DaveGamble/cJSON.git
pushd cJSON

cp LICENSE ../cJSON_LICENSE

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(realpath ../../) ..
make
make install

popd

rm -rf cJSON
