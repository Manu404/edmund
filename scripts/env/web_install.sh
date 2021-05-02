#!/bin/bash

sudo apt-get install git

git clone https://github.com/Manu404/Edmund

cd Edmund

bash ./gollum.sh install:gollum

gollum install:devenv

gollum init
