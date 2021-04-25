#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "model.h"

namespace Edmund {

  class Game
  {
    public:
      Game();
      void UpdatePlayerPropertyValue(byte player, PlayerProperties property, int delta);
      int GetPlayerPropertyValue(byte player, PlayerProperties property);
      byte GetPropertyCount();
      byte GetPlayerCount();
      byte GetManaTypeCount();
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
