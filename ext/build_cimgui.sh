#!/bin/bash

if [ -e lib/cimgui.so -a -e lib/sdl3Impl.a ]; then
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

git clone --recurse-submodules --shallow-submodules --recursive --depth 1 https://github.com/Arhcout/cimgui.git
pushd cimgui

cp LICENSE ../cimgui_LICENSE
cp imgui/LICENSE.txt ../imgui_LICENSE

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_INSTALL_PREFIX=$(realpath ../../lib) ..
make
make install

popd

cp cimgui/cimgui.h include
cp cimgui/generator/output/cimgui_impl.h include
make cimgui_impl IMPL=SDL3

make IMPL=SDL3 imgui_impl

rm -rf cimgui
