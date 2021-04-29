#!/bin/bash
SCRIPTPATH="$(readlink -f "$0")"
cd "$(dirname $SCRIPTPATH)"

cd ./scripts


while test $# -gt 0; do
  case "$1" in
    init)
		echo "Default init."
		./init.sh
		exit 0
		;;
	install:gollum)
		echo "Make gollum userly available (ln in ~/bin/gollum"
		ln -s `pwd`/gollum.sh ~/bin/gollum
		chmod +x ~/bin/gollum
		exit 0;
		;;
	install:cli)
		echo "Install cli"
		./instal_cli.sh
		exit 0
		;;
	install:deps)
		echo "Install dependencies"
		./install_dependencies.sh
		exit 0
		;;
	install:esp-arduino-sdk)
		echo "Install esp sdk"
		./install_esp_arduino_sdk.sh
		exit 0
		;;
	install:decoder)
		echo "Install esp stacktrace decoder"
		./innstall_esp_decoder.sh
		exit 0
		;;	
	install:espressif-toolchain)
		echo "Install espressif toolchain"
		./install_espressif_toolchain.sh
		exit 0
		;;	
	install:apt)
		echo "Install packages required from apt"
		./apt_install.sh
		exit 0
		;;
	build:bin)
		echo "Build current code base"
		./build.sh
		exit 0
		;;		
	build:test)
		echo "Build tests"
		./build_test.sh
		exit 0
		;;	
	build:clean)
		echo "Clean build output/tmp, then build"
		./cleanbuild.sh
		exit 0
		;;	
	clean:all)
		echo "Clean build output/tmp"
		./clean.sh
		./clean_test.sh
		exit 0
		;;
	clean:test)
		echo "Clean test output/tmp"
		./clean_test.sh
		exit 0
		;;
	run:flash)
		echo "Flash the device with edmmund"
		./upload.sh
		exit 0;
		;;
	run:test)
		echo "Build and run unit tests"
		./build_run_test.sh
		exit 0
		;;
	run:debug)
		echo "Clean build, upload and start serial monitor"
		./debug.sh
		exit 0
		;;
	serial)
		echo "Start serial monitor"
		./openserial.sh
		exit 0
		;;
	screen)
		echo "Launch dev screen"
		./startscreen.sh
		exit 0
		;;
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
