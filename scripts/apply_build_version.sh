#!/bin/bash

sed -i "s/#define EDMUND_VERSION.*/#define EDMUND_VERSION \"$(cat ../edmund/version)\"/g" ../edmund/src/version.h
