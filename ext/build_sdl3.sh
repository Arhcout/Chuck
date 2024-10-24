#!/bin/bash

if [ -e lib/libSDL3.so ]; then
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

git clone https://github.com/libsdl-org/SDL
pushd SDL

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release --install-prefix=$(realpath ../../) ..

cmake --build . --config Release --parallel

cmake --install . --config Release

popd

rm -rf SDL
