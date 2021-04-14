#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "./player.h"

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
    Player Me;
    Player Opponents[3];
    ManaPoolState ManaPool;
};

class Game 
{
  public:
    Game();
    String GetOpponentLifeLine();
    String GetCommanderDamages();
    String GetReceivedCommanderDamages();
    void MoveRight();
    void MoveLeft();
    String GetCurrentPosition();
    void UpdateCurrentProperty(int delta);
    void UpdateCurrentPropertyFromPot(int current);
    GameState state;   
  private:
    String space = "";
    String FormatAsColumn(int a, int b, int c, int property);
    String GetFormatedValue(int value, int player, int property);
    int static const opponentCount = 3;  
    int currentProperty = 0;
    int currentPlayer = 0;
    int propertyCount = 3;
};

#endif
