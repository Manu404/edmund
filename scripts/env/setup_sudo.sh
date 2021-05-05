#!/bin/bash

#that good ol' debbie, let's not act like savages and query sir sudo... he-oh he-oh ?
if ! command -v sudo &> /dev/null
then
	apt-get update
	apt-get install sudo
	/sbin/groupadd sudoers
	/sbin/usermod -aG sudoers $LOGNAME
	/sbin/reboot
fi

