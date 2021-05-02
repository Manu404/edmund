#!/bin/bash

#that good ol' debbie, let's not act like savages and query sir sudo... he-oh he-oh ?
if ! command -v sudo &> /dev/null
then
	su
	apt-get update
	apt-get install sudo
	/sbin/usermod -aG sudoers eis
	/sbin/reboot
fi

sudo apt-get update
sudo apt-get install open-vm-tools

sudo apt-get install git

sudo apt-get install bc

sudo apt-get install curl

#should be installed, juste make sure
sudo apt-get install wget
