#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "./player.h"


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class ManaPoolState {
  public:
    int W;
    int U;
    int B;
    int R;
    int G;
    int X;
};

class GameState {
  public:
    Player Players[PLAYER_COUNT];
    ManaPoolState ManaPool;
};

class Game 
{
  public:
    Game();
    void UpdateCurrentProperty(int delta, int player, int property);
    GameState state;   
    int GetPropertyCount();
    int GetPlayerCount();
  private:
    String space = "";
};

#endif
