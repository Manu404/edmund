#!/bin/bash


./update_build_version.sh
./apply_build_version.sh

cd ../edmund/

#will || build, contains: MAKEFLAGS += -j $(BUILD_THREADS) [= nproc]
make -f ../sdk/espmake/makeEspArduino.mk