#include "./game.h"


Game::Game(){
  //for(int i = 0; i < GetPlayerCount(); i++)
  //{
  //  state.Players[GetPlayerCount()].Life = 40;
  //}  
}

void Game::UpdateCurrentProperty(int delta, int player, int property){
  if(delta == 0) return;
  if (player < 0 || player > GetPlayerCount()) return;
  if (property < 0 || property > GetPropertyCount() + GetManaTypeCount()) return;

  switch(property){
    case 0:
    case 1:
    case 2:
    case 3:
      state.Players[player].ApplyDeltaToCommanderDamages(delta, property + (property >= player)); break;
    case 4: state.Players[player].ApplyDeltaToLife(delta); break;
    case 5: state.Players[player].ApplyDeltaToInfect(delta); break;
    default: state.ManaPool.ApplyDeltaToManaPoolContent((ManaType)(property - W_MANA_property), delta); break;
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