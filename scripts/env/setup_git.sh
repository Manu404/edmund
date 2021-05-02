#!/bin/bash

#should be installed, juste make sure
sudo apt-get install wget

sudo apt-get install git

git clone https://github.com/Manu404/Edmund
git config --global user.name "eis"
git config --global user.email "istace.emmanuel@hotmail.com"
git config --global credential.helper cache

cd Edmund

bash ./gollum.sh install:gollum

gollum install:devenv

gollum init
