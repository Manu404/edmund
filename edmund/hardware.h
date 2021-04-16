#ifndef HARDWARE_INCLUDED
#define HARDWARE_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include "ESPFlash.h"
#include "game.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CURRENT_GAME_STATE_PATH "/currentGame"
#define BKP_GAME_STATE_PATH "/bkpGame"
#define TARGET_FPS 30
#define FRAME_DURATION_MS 1000 / TARGET_FPS

#define SERIAL_SPEED 115200

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
    void PrintSymbol(int x_pos, int y_pos, const uint8_t *logo);
    void PrintSmallNumeric(int x_pos, int y_pos, int value, uint16_t color, int length);
    void DrawScreen(const uint8_t* screen);
    void DrawBox(int x, int y, int w, int h, uint16_t color);
    String GetDebugLine();
    void SaveStateToSpiff(GameState& state);
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
};


#endif
