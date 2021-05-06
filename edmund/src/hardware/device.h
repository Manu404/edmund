#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#define ARDUINO 180

#include <Arduino.h>  
#include <SPI.h>  
#include <ESPFlash.h>
#include <ESP8266WiFi.h>

#include "../model.h"
#include "./output/outputapi.h"
#include "./input/inputapi.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"

#define SERIAL_SPEED 115200

#define SLEEP_TICK_LIMIT 200
#define SLEEP_TIME 1000

namespace Edmund {
  using namespace Hardware;
    class Device
    {
    public:
      Device();
      Device(IOutputDevice* outputDevice, IInputDevice* inputDevice, ESPFlash<GameState>* stateArray, PinMapping mapping);
      void Initialize();
      void BeginFrame();
      void EndFrame(const GameState& game);
      void SaveStateToSpiffs(const GameState& game);
      GameState LoadStateFromSpiffs();
      IOutputDevice* GetOutput() const { return outputDevice; };
      IInputDevice* GetInput() const { return inputDevice; };
    private:
      void startLightSleep();
      void ensureSleep(const GameState& game);
      void waitRemainingFrameTime();
      ESPFlash<GameState>* stateArray;
      IOutputDevice* outputDevice;
      IInputDevice* inputDevice;
      unsigned long frameStart = 0, frameDuration = 0;
      int debug_combination = -1, sleepTick = 0;
      bool sleeping = false;
    };
}
#endif
