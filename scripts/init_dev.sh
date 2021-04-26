#!/bin/bash

sudo ./apt_install.sh

./install_cli.sh
./install_dependencies.sh
./install_esp_decoder.sh

./clean.sh
./build.sh

