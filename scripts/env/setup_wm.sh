#!/bin/bash

sudo apt-get install xorg
sudo apt-get install i3

cp ./xinitrc ~/
mv ~/xinitrc ~/.xinitrc

cp ./xresource ~/
mv ~/xresource ~/.Xresources

mkdir -p ~/.i3
cp ./i3config ~/.i3/

sudo usermod -aG video eis
sudo usermod -aG tty eis
sudo usermod -aG input eis
