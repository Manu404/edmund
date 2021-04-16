#include "./game.h"


Game::Game(){
}

void Game::UpdatePlayerProperty(int delta, int player, PlayerProperties property){
  if(delta == 0) return;
  if (player < 0 || player > GetPlayerCount()) return;
  if (property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return;

  switch(property){
    case 0:
    case 1:
    case 2:
    case 3: state.Players[player].ApplyDeltaToCommanderDamages(delta, (int)property);  break;
    case 4: state.Players[player].ApplyDeltaToLife(delta); break;
    case 5: state.Players[player].ApplyDeltaToInfect(delta); break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: state.ManaPool.ApplyDeltaToManaPoolContent((ManaType)(property - W_MANA_property), delta); break;
    default: break;
  }
}
int Game::GetPlayerProperty(int player, PlayerProperties property) {
  if (player < 0 || player > GetPlayerCount() || property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return -1;

  switch (property) {
  case 0:
  case 1:
  case 2:
  case 3: return state.Players[player].GetCommanderDamages((int)property);
  case 4: return state.Players[player].GetLife();
  case 5: return state.Players[player].GetInfect();
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11: return state.ManaPool.GetManaPoolContent((ManaType)(property - W_MANA_property));
  default: return -1;
  }
}
int Game::GetPropertyCount() {
  return PROPERTY_COUNT;
}
int Game::GetPlayerCount() {
  return PLAYER_COUNT ;
}
int Game::GetManaTypeCount() {
  return MANA_TYPE_COUNT;
}
void Game::Reset() {
  state = GameState();
}
const GameState Game::GetState() {
  return state;
}
void Game::LoadState(GameState newState) {
  state = newState;
}