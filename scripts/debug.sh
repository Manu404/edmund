#!/bin/bash

./clean.sh && ./build_tests.sh && ./run_tests.sh && ./build.sh && ./upload.sh && ./openserial.sh
