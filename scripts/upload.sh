#/bin/bash

platform='unknown'
unamestr=`uname -o`

if [[ "$unamestr" == 'Msys' ]]; then
   platform='ms'
elif [[ "$unamestr" == 'GNU/Linux' ]]; then
   platform='linux'
fi

if [[ $platform == 'ms' ]]; then
	./abn upload -i ../output/edmund.ino.bin -b esp8266:esp8266:nodemcuv2:xtal=80 -p COM3 --verbose
elif [[ $platform == 'linux' ]]; then
	./abn upload -i ../output/edmund.ino.bin -b esp8266:esp8266:nodemcuv2:xtal=80 -p /dev/ttyS3 --verbose
fi

