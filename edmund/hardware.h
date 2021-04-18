#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include <Adafruit_MCP23017.h>
#include <Wire.h>


#include "ESPFlash.h"
#include "game.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"
#define TARGET_FPS 120
#define FRAME_DURATION_MS 1000 / TARGET_FPS

#define SERIAL_SPEED 115200

struct UIMapping {
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

class Hardware 
{
  public:
    Hardware();
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
    Adafruit_PCD8544 lcd = Adafruit_PCD8544(D0, D1, D3, D4, D2);

  private:  
    ESPFlash<GameState> stateArray = ESPFlash<GameState>("/currentGame");
    void initScreen();
    void initInputs();
    int isPressed(int prev, int curr);
    UIState current, previous;
    UIMapping mapping;
    void refreshInputs();
    UIState getState();
    void clear();
    void display();
    int debug_combination = -1;
    unsigned long frameStart = 0;
    long frameDuration = 0;
    TwoWire wire;

    int previous_encoder_value = 0, current_encoder_value = 0;
};


#endif
