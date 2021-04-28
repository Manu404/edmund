#!/bin/bash

sudo apt-get install gcc git wget make libncurses-dev flex bison gperf python python-serial
sudo apt-get install python-pip

mkdir -p ~/esp
cd ~/esp
wget https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
tar -xzf xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz
export PATH="$PATH:$HOME/esp/xtensa-lx106-elf/bin"

cd ~/esp
git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git
cd <TODO>
python -m pip install --user -r $IDF_PATH/requirements.txt