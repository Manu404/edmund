#include "game.h"
 
namespace Edmund {
  Game::Game() {
    ellapsedTime = 0;
  }

  // it smells good in here
  void Game::ApplyDeltaToPlayerProperty(const byte player, const PlayerProperties property, const int delta) {
    if (delta == 0) return;
    if (player < 0 || player > GetPlayerCount()) return;
    if (property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return;

    if(property < 4)
      state.Players[player].ApplyDeltaToCommanderDamages((byte)property, delta);
    else if(property == 4)
      state.Players[player].ApplyDeltaToLife(delta);
    else if(property == 5)
      state.Players[player].ApplyDeltaToInfect(delta);
    else if(property < 12)
      state.ManaPool[player].ApplyDeltaToManaPoolContent((ManaType)(property - W_MANA_property), delta);
  }

  // yup, kind of a refrehsing odor
  int Game::GetPlayerPropertyValue(const byte player, const PlayerProperties property) const {
    if (player < 0 || player > GetPlayerCount() || property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return 0;

    if(property < 4)
      return state.Players[player].GetCommanderDamages((byte)property);
    if(property == 4)
      return state.Players[player].GetLife();
    if(property == 5)
      return state.Players[player].GetInfect();
    if(property < 12)
      return state.ManaPool[player].GetManaPoolContent((ManaType)(property - W_MANA_property));
    
    return 0;
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

  void Game::EmptyManaPools() {
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