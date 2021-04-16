#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "./player.h"

#define PROPERTY_COUNT 6
enum PlayerProperties {
  Commander_1_property = 0,
  Commander_2_property = 1,
  Commander_3_property = 2,
  Commander_x_property = 3,
  Life_property = 4,
  Infect_property = 5,
  W_MANA_property = 6,
  U_MANA_property = 7,
  R_MANA_property = 8,
  B_MANA_property = 9,
  G_MANA_property = 10,
  X_MANA_property = 11
};

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
  private:
    int pool[MANA_TYPE_COUNT];
  public:

    ManaPoolState() {
      Empty();
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

    void Empty() {
      for (int i = 0; i < MANA_TYPE_COUNT; pool[i] = 0, i++);
    }
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
    void UpdatePlayerProperty(int delta, int player, PlayerProperties property);
    int GetPlayerProperty(int player, PlayerProperties property);
    int GetPropertyCount();
    int GetPlayerCount();
    int GetManaTypeCount(); 
    void Reset();
    const GameState GetState();
    void LoadState(GameState newState);
  private:
    String space = "";
    GameState state;
};

#endif
