#!/bin/bash

# - install depends tools
# yum -y install libuuid-devel
# apt -y install uuid-dev
#

# pushd thirdparty/depends_path
# libtoolize && aclocal && autoheader && autoconf && automake --add-missing
# sh configure
# popd

rm -rf build
mkdir -p build
pushd build

cmake -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo -- -j$(nproc)

popd

# popd

# echo continue && read -n 1