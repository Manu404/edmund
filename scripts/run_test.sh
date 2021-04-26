#!/bin/sh
cd ../edmund/test/
set -eu
cd -- "$(dirname -- "$0")"
cd build
ctest -V

