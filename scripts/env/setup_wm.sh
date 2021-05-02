#!/bin/bash

sudo apt-get install xorg
sudo apt-get install i3
cp ./xinitrc ~/
makedir ~/.i3
cp ./i3config ~/.i3/config
