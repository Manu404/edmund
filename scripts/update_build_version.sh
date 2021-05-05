#!/bin/bash

./increment_build_version.sh $(cat ../edmund/version) build > ../edmund/version
