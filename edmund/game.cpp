#include "./game.h"

Game::Game(){
  state.Me = Player();
  for(int i = 0; i < opponentCount; i++)
  {
    state.Opponents[opponentCount].Life = 52;
  }  
}

String Game::GetFormatedValue(int value, int player, int property){
  String cursor_char = (currentProperty == property && currentPlayer == player) ? "*" : " ";
  if(value < 10) return "  " + cursor_char + String(value);
  if(value < 100) return " " + cursor_char + String(value);
  if(value < 1000) return "" + cursor_char + String(value);
  return "???";
}

String Game::GetOpponentLifeLine(){
  return "*" + FormatAsColumn(state.Opponents[0].Life, state.Opponents[1].Life, state.Opponents[2].Life, 0);
}

String Game::GetCommanderDamages(){
  return "D" + FormatAsColumn(state.Opponents[0].CommanderDamages, state.Opponents[1].CommanderDamages, state.Opponents[2].CommanderDamages, 1);
}

String Game::GetReceivedCommanderDamages(){
  return "R" + FormatAsColumn(state.Opponents[0].ReceivedCommanderDamages, state.Opponents[1].ReceivedCommanderDamages, state.Opponents[2].ReceivedCommanderDamages, 2);
}

void Game::MoveRight(){
  if(currentPlayer == opponentCount - 1){
    currentPlayer = 0;
    if(currentProperty == propertyCount - 1)
      currentProperty = 0;
    else
      currentProperty += 1;
  }
  else {
    currentPlayer +=1;
  }
}

void Game::MoveLeft(){
  if(currentPlayer == 0){
    currentPlayer = opponentCount - 1;
    if(currentProperty == 0)
      currentProperty = propertyCount - 1;
    else
      currentProperty -= 1;
  }
  else {
    currentPlayer -=1;
  }
}

void Game::UpdateCurrentProperty(int delta){
  if(delta == 0) return;
  switch(currentProperty){
    case 0: state.Opponents[currentPlayer].ApplyDeltaToLife(delta); break;
    case 1: state.Opponents[currentPlayer].ApplyDeltaToCommanderDamages(delta); break;
    case 2: state.Opponents[currentPlayer].ApplyDeltaToReceivedCommanderDamages(delta); break;
    default: break;
  }
}


String Game::FormatAsColumn(int a, int b, int c, int property){
  return GetFormatedValue(a, 0, property) + space + GetFormatedValue(b, 1, property) + space + GetFormatedValue(c, 2, property);
}

String Game::GetCurrentPosition(){
  return "(" + String(currentPlayer) + ", " + String(currentProperty) + ")";
}

void Game::UpdateCurrentPropertyFromPot(int current) {
  currentPlayer = current % 3;
  currentProperty = current / 3;
}
