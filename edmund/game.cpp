#include "./game.h"

Game::Game(){
  for(int i = 0; i < GetPlayerCount(); i++)
  {
    state.Players[GetPlayerCount()].Life = 52;
  }  
}

void Game::UpdateCurrentProperty(int delta, int player, int property){
  if(delta == 0) return;
  if (player < 0 || player > GetPlayerCount()) return;
  if (property < 0 || property > GetPropertyCount()) return;

  switch(property){
    case 0: state.Players[player].ApplyDeltaToCommanderDamages(delta); break;
    case 1: state.Players[player].ApplyDeltaToCommanderDamages(delta); break;
    case 2: state.Players[player].ApplyDeltaToCommanderDamages(delta); break;
    case 3: state.Players[player].ApplyDeltaToCommanderDamages(delta); break;
    case 4: state.Players[player].ApplyDeltaToLife(delta); break;
    // INFECT case 5: state.Players[player].ApplyDeltaToReceivedCommanderDamages(delta); break;
    default: break;
  }
}
int Game::GetPropertyCount() {
  return PLAYER_COUNT;
}
int Game::GetPlayerCount() {
  return PROPERTY_COUNT;
}