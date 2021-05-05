#!/bin/bash
cd ../edmund/test/

set -eu

cd -- "$(dirname -- "$0")"
mkdir -p build
cd build
cmake ..
echo "CMAKE done"
echo $(pwd)
make -j $(nproc)

