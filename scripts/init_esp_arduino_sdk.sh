#!/bin/bash
sudo apt-get install gcc

mkdir -p ../sdk/
cd ../sdk/

git clone https://github.com/plerup/makeEspArduino.git espmake

git clone https://github.com/esp8266/Arduino.git esp8266
cd esp8266
git checkout tags/2.7.4
git submodule update --init
cd tools
python3 get.py
