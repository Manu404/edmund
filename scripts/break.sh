#!/bin/bash

echo "Want play with Smeagol?"
select selection in "Go on an adventure" "Talk a bit" "Shoot stuffs" "Eat stuffs" "Nevermind, I know what you did to Deagol."; do
	case $selection in
		"Go on an adventure" ) sudo apt-get install colossal-cave-adventure && clear && colossal-cave-adventure; break;;
		"Talk a bit" ) 	exit;;
		"Eat stuffs" ) sudo apt-get install pacman4console && pacman4console; exit;;
		"Shoot stuffs" ) sudo apt install ninvaders && ninvaders; exit;; 
		"Nevermind, I know what you did to Deagol." ) exit;;
	esac
done