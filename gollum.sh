#!/bin/bash
SCRIPTPATH="$(readlink -f "$0")"
cd "$(dirname $SCRIPTPATH)"

cd ./scripts

while test $# -gt 0; do
  case "$1" in
	settle)
		echo "Gollum got a new home! (ln in ~/bin/gollum, make it globally available for current user)"
		./install_gollum.sh
		exit;;
	init)
		echo "Default init."; 
		time ./init.sh; 
		exit;;
	install:cli)
		echo "Install cli"; 
		./install_cli.sh; 
		exit;;
	install:deps)
		echo "Install dependencies"; 
		./install_dependencies.sh; 
		exit;;
	install:esp-arduino-sdk)
		echo "Install esp sdk"; 
		./install_esp_arduino_sdk.sh; 
		exit;;
	install:decoder)
		echo "Install esp stacktrace decoder"
		./install_esp_decoder.sh; 
		exit;;	
	install:espressif-toolchain)
		echo "Install espressif toolchain"
		./install_espressif_toolchain.sh; 
		exit;;	
	install:apt)
		echo "Install packages required available through apt"
		./install_apt.sh; 
		exit;;
		
	build:all)
		echo "Build current code base"
		time ./build_bin.sh; 
		time ./build_test.sh; 
		exit;;			
	build:bin)
		echo "Build current code base"
		time ./build_bin.sh; 
		exit;;		
	build:test)
		echo "Build tests"
		time ./build_test.sh; 
		exit;;	
	build:clean)
		echo "Clean build output/tmp, then build"
		./clean.sh; 
		time ./build_bin.sh; 
		exit;;	

	clean:all)
		echo "Clean build output/tmp"
		./clean_build.sh; 
		./clean_test.sh; 
		./clean_testdep.sh; 
		exit;;
	clean:bin)
		echo "Clean build output/tmp"
		./clean_bin.sh; 
		exit;;
	clean:test)
		echo "Clean test"; 
		./clean_test.sh; 
		exit;;
	clean:testall)
		echo "Clean test + dependencies"; 
		./clean_testdep.sh; 
		exit;;

	purge:all)
		echo "Purge test output/tmp"; 
		./purge_test.sh; 
		./purge_bin.sh; 
		exit;;
	purge:test)
		echo "Purge test output/tmp"; 
		./purge_test.sh; 
		exit;;
	purge:bin)
		echo "Purge test output/tmp"; 
		./purge_bin.sh; 
		exit;;

	run:flash)
		echo "Flash the device with edmmund"; 
		time ./build_bin.sh; 
		./upload.sh; 
		exit;;
	run:test)
		echo "Build and run unit tests"; 
		time ./build_test.sh
		./run_test.sh
		exit;;
	run:debug)
		echo "Clean build, upload and start serial monitor"; 
		./debug.sh; 
		exit;;
	run:to:mordor)
		./break.sh; 
		exit;;
	run:serial)
		echo "Start serial monitor"; 
		./run_serial.sh; 
		exit;;
	run:screen)
		echo "Launch dev screen"; 
		./run_screen.sh; 
		exit;;

	help)
		echo "======================================================================================"
		echo "=============== b e == c a r e f u l./:%£*¨%µ%*jdj'*¨£%$^)z¨^àçgu^ ============ damn ="
		echo "======================================================================================"
		echo "  init .................................. Default init. (init.sh)"
		echo "  install:gollum ........................ Make gollum available in shell, usage: gollum <args>"
		echo "         :cli ........................... Install cli"
		echo "         :deps .......................... Install dependencies"
		echo "         :esp-arduino-sdk ............... Install esp sdk"
		echo "         :decoder ....................... Install esp stacktrace decoder"
		echo "         :espressif-toolchain............ Install espressif toolchain"
		echo "         :apt ........................... Install packages required from apt"
		echo "  build:bin ............................. Build current code base"
		echo "       :test ............................ Build tests"
		echo "       :clean ........................... Clean build output/tmp, then build"
		echo "  clean:all ............................. Clean build output/tmp"
		echo "       :bin ............................. Clean build output/tmp"
		echo "       :test ............................ Clean build output/tmp"
		echo "  run:flash ............................. Fash the device with edmund"
		echo "     :test .............................. Build and run unit tests"
		echo "     :debug ............................. Clean build, upload and start serial monitor"
		echo "  serial ................................ Start serial monitor"
		echo "  screen ................................ Launch dev screen"
		exit 0
		;;
	*)
	  echo "Unknown order, type 'gollum help' for available commands"
      break
      ;;
  esac
done
