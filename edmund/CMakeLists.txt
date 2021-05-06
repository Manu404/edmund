cmake_minimum_required(VERSION 3.14)
project(edmundFlash)

include_directories(
    /home/eis/Edmund/edmund/../sdk/esp8266/libraries/SPI
    /home/eis/Edmund/edmund/../sdk/esp8266/libraries/Wire
    /home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src 
    /home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/include 
    /home/eis/Arduino/libraries/Adafruit_BusIO 
    /home/eis/Arduino/libraries/Adafruit_GFX_Library 
    /home/eis/Arduino/libraries/Adafruit_GFX_Library/Fonts 
    /home/eis/Arduino/libraries/Adafruit_MCP23017_Arduino_Library 
    /home/eis/Arduino/libraries/Adafruit_PCD8544_Nokia_5110_LCD_library 
    /home/eis/Arduino/libraries/ESPFlash/src 

    ../sdk/esp8266/cores/esp8266/
    ../sdk/esp8266/tools/sdk/include/
    ../sdk/esp8266/tools/sdk/lwip/include
    ../sdk/esp8266/tools/sdk/libc/xtensa-lx106-elf/include

    ../sdk/esp8266/tools/xtensa-lx106-elf/xtensa-lx106-elf/include/c++/4.8.2

    ../sdk/esp8266/variants/nodemcu/

    /home/eis/Edmund/edmund/src
    /home/eis/Edmund/edmund/src/ui
    /home/eis/Edmund/edmund/src/hardware
    /home/eis/Edmund/edmund/src/hardware/input
    /home/eis/Edmund/edmund/src/hardware/output
)


file(GLOB SRCS 
/home/eis/Arduino/libraries/Adafruit_BusIO/Adafruit_BusIO_Register.cpp 
/home/eis/Arduino/libraries/Adafruit_BusIO/Adafruit_I2CDevice.cpp 
/home/eis/Arduino/libraries/Adafruit_BusIO/Adafruit_SPIDevice.cpp 
/home/eis/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.cpp 
/home/eis/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GrayOLED.cpp 
/home/eis/Arduino/libraries/Adafruit_GFX_Library/Adafruit_SPITFT.cpp 
/home/eis/Arduino/libraries/Adafruit_GFX_Library/glcdfont.c 
/home/eis/Arduino/libraries/Adafruit_MCP23017_Arduino_Library/Adafruit_MCP23017.cpp 
/home/eis/Arduino/libraries/Adafruit_PCD8544_Nokia_5110_LCD_library/Adafruit_PCD8544.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/BearSSLHelpers.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/CertStoreBearSSL.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFi.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiAP.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiGeneric.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiGratuitous.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiMulti.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiSTA-WPS.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiSTA.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/ESP8266WiFiScan.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiClient.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiClientSecureAxTLS.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiClientSecureBearSSL.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiServer.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiServerSecureAxTLS.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiServerSecureBearSSL.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/ESP8266WiFi/src/WiFiUdp.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/SPI/SPI.cpp 
/home/eis/Edmund/edmund/../sdk/esp8266/libraries/Wire/Wire.cpp 
/home/eis/Edmund/edmund/./src/game.cpp 
/home/eis/Edmund/edmund/edmund.ino 
/home/eis/Edmund/edmund/src/**/*.cpp
) 

add_executable(edmundFlash ${SRCS})

target_link_libraries(edmundFlash
    ${CMAKE_THREAD_LIBS_INIT}
)

add_definitions( -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1
                 -DARDUINO_ESP8266_NODEMCU -DESP8266 -DARDUINO_ARCH_ESP8266 -DARDUINO_BOARD=\"ESP8266_NODEMCU\"  
                 -DARDUINO=10605  )

target_precompile_headers(edmundFlash PRIVATE ../sdk/esp8266/cores/esp8266/Arduino.h)

set(CMAKE_C_COMPILER "../sdk/esp8266/tools/xtensa-lx106-elf/bin/xtensa-lx106-elf-gcc")
set(CMAKE_CXX_COMPILER "../sdk/esp8266/tools/xtensa-lx106-elf/bin/xtensa-lx106-elf-g++")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_C_FLAGS "-w -Os -g -std=gnu99 -D__GNUC__=1 -Wpointer-arith -Wno-implicit-function-declaration -Wundef -pipe -D__ets__ -DICACHE_FLASH -fno-inline-functions -ffunction-sections -nostdlib -mlongcalls -mtext-section-literals -falign-functions=4 -fdata-sections -DF_CPU=80000000L" CACHE STRING "C compiler flags" FORCE)
set(CMAKE_CXX_FLAGS "-w -Os -g -D__ets__ -D__GNUC__=1 -DICACHE_FLASH -mlongcalls -mtext-section-literals -fno-exceptions -fno-rtti -falign-functions=4 -std=c++11 -MMD -ffunction-sections -fdata-sections -DF_CPU=80000000L" CACHE STRING "CXX compiler flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -Wl,--no-check-sections -Wl,-static -Wl,--gc-sections -L../sdk/esp8266/tools/sdk/ld -Teagle.flash.${ESP8266_FLASH_SIZE}.ld -u call_user_start -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy" CACHE STRING "linker flags" FORCE)

set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -o <TARGET> -Wl,--start-group <OBJECTS> <LINK_LIBRARIES> -Wl,--end-group" CACHE STRING "C linker invocation")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -o <TARGET> -Wl,--start-group <OBJECTS> <LINK_LIBRARIES> -Wl,--end-group" CACHE STRING "CXX linker invocation")
