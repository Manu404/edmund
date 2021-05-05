#!/bin/bash

sudo /etc/init.d/screen-cleanup start
screen -S edmund -c ./env/screenrc
