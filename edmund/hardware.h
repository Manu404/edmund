#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h> 
#include "ESPFlash.h"
#include "game.h"

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"

#define SERIAL_SPEED 19200

struct UIMapping {
  int right = D5;
  int middle = D6;
  int left = D7;
  int pot = A0;
};

struct UIState {
  int right;
  int middle;
  int left;
  int pot;
  int debug;
  int reset;
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
    int IsMiddlePressed();
    int IsDebugPressed();
    int IsResetPressed();
    int HasPotChanged();
    float GetPositionFromPot(float scale);
    void Print(String m);
    void PrintLine(String m);
    void DrawSymbol(int x_pos, int y_pos, const uint8_t *logo);
    void DrawScreen(const uint8_t* screen);
    String GetDebugLine();
    void SaveStateToSpiff(GameState state);
    GameState LoadStateFromSpiff();
  private:
    Adafruit_PCD8544 lcd = Adafruit_PCD8544(D0, D1, D3, D4, D2);    
    ESPFlash<GameState> stateArray = ESPFlash<GameState>(CURRENT_GAME_STATE_PATH);
    void initScreen();
    void initInputs();
    float getPotValue();
    int isPressed(int prev, int curr);
    UIState current, previous;
    UIMapping mapping;
    void refreshInputs();
    UIState getState();
    void clear();
    void display();
    int debug_combination = -1;
};

#endif
