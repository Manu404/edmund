#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include <SPI.h>  
#include "ESPFlash.h"

#include "../game.h"
#include "mcp_provider.h"
#include "lcd_provider.h"
#include "input_provider.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"

#define SERIAL_SPEED 115200

namespace Edmund {
  namespace Hardware {
    class Device : public LcdProvider, public InputProvider
    {
    public:
      Device();
      Device(Adafruit_PCD8544* lcd, McpProvider* mcp, ESPFlash<GameState>* stateArray, PinMapping mapping);
      void Initialize();
      void BeginFrame();
      void EndFrame();
      String GetDebugLine();
      void SaveStateToSpiff(const GameState& state);
      GameState LoadStateFromSpiff();
    private:
      ESPFlash<GameState>* stateArray;
      unsigned long frameStart = 0;
      long frameDuration = 0;
      int debug_combination = -1;
    };
  }
}
#endif
