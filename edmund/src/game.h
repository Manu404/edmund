#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "model.h"

namespace Edmund {

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
      void RefreshEllapsedTime();
    private:
      String space = "";
      GameState state;
      unsigned long ellapsed_time, last_time;
  };
}
#endif
