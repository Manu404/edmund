#!/bin/bash

cd ../
mkdir -p ~/bin/
ln -sf $(pwd)/gollum.sh ~/bin/gollum
sudo chmod +x ~/bin/gollum
source ~/.profile
