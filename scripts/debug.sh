#!/bin/bash

./clean.sh && ./build_test.sh && ./run_test.sh && ./build.sh && ./upload.sh && ./openserial.sh
