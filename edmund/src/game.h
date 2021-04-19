#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "player.h"
#include "mana.h"

namespace Edmund {
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
      const GameState GetGameState();
      void LoadGameState(GameState newState);
    private:
      String space = "";
      GameState state;
  };
}
#endif
