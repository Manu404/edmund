#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Arduino.h>
#include "model.h"

namespace Edmund {

  class Game
  {
    public:
      Game();
      void ApplyDeltaToPlayerProperty(const byte player, const PlayerProperties property, const int delta);
      int GetPlayerPropertyValue(const byte player, const PlayerProperties property) const;
      const byte GetPropertyCount() const;
      const  byte GetPlayerCount() const;
      const byte GetManaTypeCount() const;
      void Reset();
      const GameState GetGameState() const;
      void LoadGameState(GameState newState);
      void RefreshEllapsedTime();
      void EmptyManaPool();
    private:
      String space = "";
      GameState state;
      unsigned long ellapsedTime, lastTime;
  };
}
#endif
