THIS_DIR := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
ROOT := $(THIS_DIR)

SKETCH = edmund.ino

ESP_ROOT = /home/eis/esp8266

UPLOAD_PORT = /dev/ttyS3

BUILD_DIR = $(ROOT)/../build

ARDUINO_LIBS := /home/eis/Arduino/libraries

BOARD = nodemcuv2

LIBS = $(ESP_LIBS)/SPI \
       $(ESP_LIBS)/Wire \
	$(ESP_LIBS)/ESP8266WiFi \
	$(ESP_LIBS)/ESP8266WebServer \
	$(ARDUINO_LIBS)/Adafruit_BusIO \
	$(ARDUINO_LIBS)/Adafruit_GFX_Library \
	$(ARDUINO_LIBS)/Adafruit_MCP23017_Arduino_Library \
	$(ARDUINO_LIBS)/Adafruit_PCD8544_Nokia_5110_LCD_library \
	$(ARDUINO_LIBS)/ESPFlash/src \

EXCLUDE_DIRS := $(ROOT)/test/*
