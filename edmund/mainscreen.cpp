#include "mainscreen.h"

Mainscreen::Mainscreen() {

}

int current_player;
int current_property;
int currentPosition = NULL;

void Mainscreen::print(Hardware& hardware, Game& game) {
  int y = 0, x = 0, col_margin = 2, life_column = 4, infect_column = 5;
  uint16_t color = BLACK;

  hardware.DrawScreen(mainlayout);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 6; col++) {
      if (col == 5) { // if infect, map to bottom row
        x = col_size + 6 + (row * col_size) + col_margin;
        y = row_size + (4 * row_size) + row_margin;
      }
      else {
        x = col_size + 6 + (col * col_size) + col_margin;
        y = row_size + (row * row_size) + row_margin;
      }

      if (col == life_column) x = 0;

      if (col >= row && col < life_column) x += col_size;

      if (row == current_player && col == current_property) {
        hardware.lcd.fillRect(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
        color = WHITE;
      }

      if (col == infect_column) {
        hardware.PrintSmallNumeric(x, y, game.state.Players[row].Infect, color, 2);
      }
      else if (col < life_column) {
        hardware.PrintSmallNumeric(x, y, game.state.Players[row].CommanderDamages[col], color, 2);
      }
      else if (col == life_column) {
        if (game.state.Players[row].Life > 99)
          hardware.PrintSmallNumeric(x, y, game.state.Players[row].Life, color, 3);
        else
          hardware.PrintSmallNumeric(x + col_margin, y, game.state.Players[row].Life, color, 2);
      }
      color = BLACK;
    }
  }
}

void Mainscreen::updatePosition()
{
  if (currentPosition < 4) {
    current_player = currentPosition;
    current_property = 4;
  }
  else if (currentPosition < 17) {
    current_player = (currentPosition - 4) / 3;
    current_property = (currentPosition - 4) % 3;
  }
  else {
    current_player = (currentPosition - 17);
    current_property = 5;
  }
}

void Mainscreen::processInputs(Hardware& hardware, Game& game)
{
  if (hardware.HasPotChanged() || currentPosition == NULL) {
    currentPosition = (hardware.GetPositionFromPot(game.GetPlayerCount() * game.GetPropertyCount()));
    updatePosition();
  }

  if (hardware.IsRightPressed() == 1)
    game.UpdateCurrentProperty(1, current_player, current_property);
  if (hardware.IsLeftPressed() == 1)
    game.UpdateCurrentProperty(-1, current_player, current_property);
  if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
    hardware.SaveStateToSpiff(game.state);

  if (hardware.IsDebugPressed() == 1)
    debug *= -1;
}

ScreenEnum Mainscreen::loop(Hardware& hardware, Game& game)
{
  processInputs(hardware, game);

  print(hardware, game);

  if (hardware.IsMiddlePressed() == 1)
    return ConfigScreenEnum;
  return MainScreenEnum;
}


void Mainscreen::legacyPrint(Hardware& hardware, Game& game) {
  //hardware.PrintLine(game.GetOpponentLifeLine());
  //hardware.PrintLine(game.GetCommanderDamages());
  //hardware.PrintLine(game.GetReceivedCommanderDamages());

  //if (debug == 1) {
  //  hardware.PrintLine(hardware.GetDebugLine());
  //  hardware.PrintLine(game.GetCurrentPosition());
  //}
}


