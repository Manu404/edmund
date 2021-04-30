#include "game.h"
 
namespace Edmund {
  Game::Game() {
    ellapsed_time = 0;
  }

  void Game::ApplyDeltaToPlayerProperty(const byte player, const PlayerProperties property, const int delta) {
    if (delta == 0) return;
    if (player < 0 || player > GetPlayerCount()) return;
    if (property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return;

    switch (property) {
    case 0:
    case 1:
    case 2: 
    case 3: state.Players[player].ApplyDeltaToCommanderDamages((byte)property, delta);  break;
    case 4: state.Players[player].ApplyDeltaToLife(delta); break;
    case 5: state.Players[player].ApplyDeltaToInfect(delta); break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: state.ManaPool[player].ApplyDeltaToManaPoolContent((ManaType)(property - W_MANA_property), delta); break;
    default: break;
    }
  }

  int Game::GetPlayerPropertyValue(const byte player, const PlayerProperties property) const {
    if (player < 0 || player > GetPlayerCount() || property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return -1;

    switch (property) {
    case 0:
    case 1:
    case 2:
    case 3: return state.Players[player].GetCommanderDamages((byte)property);
    case 4: return state.Players[player].GetLife();
    case 5: return state.Players[player].GetInfect();
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: return state.ManaPool[player].GetManaPoolContent((ManaType)(property - W_MANA_property));
    default: return -1;
    }
  }

  const byte Game::GetPropertyCount() const {
    return PROPERTY_COUNT;
  }

  const byte Game::GetPlayerCount() const {
    return PLAYER_COUNT;
  }

  const byte Game::GetManaTypeCount() const {
    return MANA_TYPE_COUNT;
  }

  void Game::Reset() {
    state = GameState();
  }

  const GameState Game::GetGameState() const {
    return state;
  }

  void Game::LoadGameState(GameState newState) {
    state = newState;
  }

  void Game::EmptyManaPool() {
    for(int i = 0; i < GetPlayerCount(); i++)
      state.ManaPool[i].Empty();
  }

  void Game::RefreshEllapsedTime() {
    // unsigned long current = millis();
    // if(last_time != 0)
    //  ellapsed_time += current - last_time;
    // last_time = current;
  }
}