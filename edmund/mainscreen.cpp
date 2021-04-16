#include "mainscreen.h"

Mainscreen::Mainscreen() {

}

ScreenEnum Mainscreen::loop(Hardware& hardware, Game& game)
{
  processInputs(hardware, game);

  print(hardware, game);

  if (hardware.IsMiddlePressed() == 1)
    return ConfigScreenEnum;
  return MainScreenEnum;
}

void Mainscreen::processInputs(Hardware& hardware, Game& game)
{
  if (hardware.HasPotChanged() || currentPosition == NULL) 
    updateNavigationPosition(hardware.GetPositionFromPot((game.GetPlayerCount() * game.GetPropertyCount()) + game.GetManaTypeCount()));

  if (hardware.IsRightPressed() == 1)
    game.UpdateCurrentProperty(1, current_player, current_property);
  if (hardware.IsLeftPressed() == 1)
    game.UpdateCurrentProperty(-1, current_player, current_property);
  if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
    hardware.SaveStateToSpiff(game.state);

  if (hardware.IsDebugPressed() == 1)
    debug *= -1;
}

void Mainscreen::updateNavigationPosition(int position)
{
  currentPosition = position;
  if (currentPosition < 6) {
    current_player = 0;
    current_property = (PlayerProperties)(6 + (currentPosition % 6));
    return;
  }

  currentPosition -= 6;

  if (currentPosition < 4) {
    current_player = currentPosition;
    current_property = Life_property;
  }
  else if (currentPosition < 16) {
    current_player = (currentPosition - 4) / 3;
    current_property = (PlayerProperties)((currentPosition - 4) % 3);
  }
  else {
    current_player = (currentPosition - 16);
    current_property = Infect_property;
  }
}

//void Mainscreen::updateProperty(int delta, Game& game)
//{
//  if (current_property < 4)
//    
//  else if (current_property == 4)
//    game.state.Players[current_player].ApplyDeltaToLife(delta);
//  else if (current_property == 5)
//    game.state.Players[current_player].ApplyDeltaToInfect(delta);
//  else {
//    // mana pool
//  }
//}

void Mainscreen::print(Hardware& hardware, Game& game) {
  int life_column = Life_property, infect_column = Infect_property;

  hardware.DrawScreen(mainlayout);

  int y = 0, x = 0;
  uint16_t color = BLACK;

  printManaPool(game, hardware);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 6; col++, color = BLACK) {
      // compute property position
      if (col != 5) {
        x = col_size + head_col_size + (col * col_size) + col_margin;
        y = row_size + (row * row_size) + row_margin;
      }
      else {
        x = col_size + head_col_size + (row * col_size) + col_margin;
        y = row_size + (4 * row_size) + row_margin;
      }
      if (col == life_column) x = 0;
      if (col >= row && col < life_column) x += col_size;

      // print selection box
      if (row == current_player && col == current_property) {
        hardware.DrawBox(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
        color = WHITE;
      }

      // print player property
      if (col == infect_column) {
        hardware.PrintSmallNumeric(x, y, game.state.Players[row].Infect, color, 2);
      }
      else if (col < life_column - 1) {
        hardware.PrintSmallNumeric(x, y, game.state.Players[row].CommanderDamages[col + (col >= row)], color, 2);
      }
      else if (col == life_column) {
        if (game.state.Players[row].Life > 99)
          hardware.PrintSmallNumeric(x, y, game.state.Players[row].Life, color, 3);
        else
          hardware.PrintSmallNumeric(x + col_margin, y, game.state.Players[row].Life, color, 2);
      }
    }
  }
}

void Mainscreen::printManaPool(Game& game, Hardware& hardware)
{
  int y = 0, x = 0;
  uint16_t color = BLACK;
  int* pool = game.state.ManaPool.GetManaPoolContent();
  x = col_size + head_col_size + (4 * col_size) + col_margin + mana_head_col_size;
  for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
    y = (i * row_size) + row_margin;
    if (current_player == 0 && (current_property - 6) == i)
    {
      hardware.lcd.fillRect(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
      color = WHITE;
    }
    hardware.PrintSmallNumeric(x, y, game.state.ManaPool.GetManaPoolContent((ManaType)i), color, 2);
  }
}