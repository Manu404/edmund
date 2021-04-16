#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "./player.h"


#define MANA_TYPE_COUNT 6
enum ManaType {
  W_MANA = 0,
  U_MANA = 1,
  R_MANA = 2,
  B_MANA = 3,
  G_MANA = 4,
  X_MANA = 5
};

class ManaPoolState {
    int pool[MANA_TYPE_COUNT];
  public:

    ManaPoolState() {
      for (int i = 0; i < MANA_TYPE_COUNT; pool[i] = 0, i++);
    }  

    int GetManaPoolContent(ManaType type) {
      return pool[type];
    }

    int ApplyDeltaToManaPoolContent(ManaType type, int delta) {
      pool[type] += delta;
      if (pool[type] < 0) pool[type] = 0;
    }

    int* GetManaPoolContent() {
      return pool;
    }
};

class GameState {
  public:
    Player Players[PLAYER_COUNT];
    ManaPoolState ManaPool;
};

#define PROPERTY_COUNT 5

enum PlayerProperties {
  Commander_1_property = 0,
  Commander_2_property = 1,
  Commander_3_property = 2,
  Life_property = 4,
  Infect_property = 5,
  W_MANA_property = 6,
  U_MANA_property = 7,
  R_MANA_property = 8,
  B_MANA_property = 9,
  G_MANA_property = 10,
  X_MANA_property = 11
};

class Game 
{
  public:
    Game();
    void UpdateCurrentProperty(int delta, int player, int property);
    GameState state;   
    int GetPropertyCount();
    int GetPlayerCount();
    int GetManaTypeCount();
  private:
    String space = "";
};

#endif
