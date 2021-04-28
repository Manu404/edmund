#pragma once
#ifndef MODEL_INCLUDED
#define MODEL_INCLUDED

#include "player.h"
#include "mana.h"

namespace Edmund {
  class GameState {
  public:
    Player Players[PLAYER_COUNT];
    ManaPoolState ManaPool[PLAYER_COUNT];
  };
}
#endif