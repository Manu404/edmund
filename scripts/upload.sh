#!/bin/bash

platform='unknown'
unamestr=`uname -o`

if [[ "$unamestr" == 'Msys' ]]; then
   platform='ms'
elif [[ "$unamestr" == 'GNU/Linux' ]]; then
   platform='linux'
fi

COMPORT=/dev/ttyS3

if [[ $platform == 'ms' ]]; then
	COMPORT=COM3
#elif [[ $platform == 'linux' ]]; then
fi

./abn upload -i ../output/edmund.ino.bin -b esp8266:esp8266:nodemcuv2:xtal=80 -p $COMPORT --verbose

