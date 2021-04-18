#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include <Adafruit_MCP23017.h>
#include <Wire.h>
#include <SPI.h>  
#include "ESPFlash.h"

#include "../game.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"
#define TARGET_FPS 120
#define FRAME_DURATION_MS 1000 / TARGET_FPS

#define SERIAL_SPEED 115200

struct PinMapping {
  int right = 1;
  int middle = 3;
  int left = 2;
  int pot = A0;
  int CLK = 1;
  int DT = 2;
};

struct UIState {
  int right;
  int middle;
  int left;
  int pot;
  int debug;
  int reset;
  int rotary_direction;
};


class McpProvider {
  Adafruit_MCP23017* current_mcp;
  TwoWire* wire;
  int ready = 0;
public:
  McpProvider() : current_mcp { new Adafruit_MCP23017() }, wire { new TwoWire() }  {  }

  void Initialize(int SDA, int SDC) {
    wire->begin(SDA, SDC);
    current_mcp->begin(wire);
    current_mcp->setupInterrupts(true, false, LOW);
    ready = 1;
  }

  int IsReady() {
    return ready;
  }

  void pinMode(int pin, int mode) {
    current_mcp->pinMode(pin, mode);
  }
  void setupInterruptPinMode(int pin, int mode, int interupt_mode) {
    current_mcp->pinMode(pin, mode);
    current_mcp->pinMode(pin, interupt_mode);
  }
  int digitalRead(int pin) {
    return current_mcp->digitalRead(pin);
  }
};

class Hardware 
{
  public:
    Hardware();
    Hardware(Adafruit_PCD8544* lcd, McpProvider* mcp, ESPFlash<GameState>* stateArray, PinMapping mapping, TwoWire wire);
    void Initialize();
    void BeginFrame();
    void EndFrame();
    int IsRightPressed();
    int IsLeftPressed();
    int GetEncoderDelta();
    int IsMiddlePressed();
    int IsDebugPressed();
    int IsResetPressed();    
    int IsEncoderTurnedRight();
    int IsEncoderTurnedLeft();
    int HasPotChanged();
    float GetPositionFromPot(float scale);
    void Print(String m);
    void PrintLine(String m);
    void PrintSymbol(int x_pos, int y_pos, const uint8_t *logo);
    void PrintSmallNumeric(int x_pos, int y_pos, int value, uint16_t color, int length);
    void DrawScreen(const uint8_t* screen);
    void DrawBox(int x, int y, int w, int h, uint16_t color);
    String GetDebugLine();
    void SaveStateToSpiff(const GameState& state);
    GameState LoadStateFromSpiff();
  private:  
    // injectable dependencies
    ESPFlash<GameState>* stateArray;
    Adafruit_PCD8544* lcd;
    PinMapping pinMapping;
    TwoWire wire;
    //Adafruit_MCP23017* mcp;
    McpProvider* mcp_provider;

    UIState current, previous;
    int debug_combination = -1;
    unsigned long frameStart = 0;
    int previous_encoder_value = 0, current_encoder_value = 0;
    long frameDuration = 0;

    void initScreen();
    void initInputs();
    int isPressed(int prev, int curr);
    void refreshInputs();
    UIState getState();
    void clear();
    void display();
};


#endif
