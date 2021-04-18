#include "mainscreen.h"

Mainscreen::Mainscreen() {

}

ScreenEnum Mainscreen::loop(Hardware& hardware, Game& game) {
  processInputs(hardware, game);
  drawLayout(hardware);
  printPlayersProperties(hardware, game);
  printManaPool(game, hardware);
  return MainScreenEnum;
}

void Mainscreen::processInputs(Hardware& hardware, Game& game) {
  if (hardware.HasPotChanged()) 
    updateNavigationPosition(hardware.GetPositionFromPot((game.GetPlayerCount() * (game.GetPropertyCount() - 1)) + game.GetManaTypeCount()));

  if (hardware.IsRightPressed() == 1)
    game.UpdatePlayerProperty(1, current_player, current_property);
  if (hardware.IsLeftPressed() == 1)
    game.UpdatePlayerProperty(-1, current_player, current_property);

  if (hardware.GetEncoderDelta() != 0)
    game.UpdatePlayerProperty(hardware.GetEncoderDelta(), current_player, current_property);

  if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
    hardware.SaveStateToSpiff(game.GetGameState());

  //if (hardware.IsDebugPressed() == 1)
  //if (hardware.IsResetPressed() == 1)
  //  game.Reset();
}

void Mainscreen::updateNavigationPosition(int position) {
  if (position < 6) {
    current_player = 0;
    current_property = (PlayerProperties)(6 + (position % 6));
    return;
  }
  position -= 6;

  if (position < 4) {
    current_player = position;
    current_property = Life_property;
    return;
  }
  position -= 4;
  
  if (position < 12) {
    current_player = (position / 3);
    current_property = (PlayerProperties)(position % 3);
    return;
  }
  position -= 12;
  current_player = position;
  current_property = Infect_property;
}

void Mainscreen::printPlayersProperties(Hardware& hardware, Game& game) {
  int y = 0, x = 0;
  int life_column = Life_property, infect_column = Infect_property;
  uint16_t color = BLACK;

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
      if (col < life_column - 1) {
        hardware.PrintSmallNumeric(x, y, game.GetPlayerProperty(row, (PlayerProperties)(col)), color, 2);
      }
      else if (col == life_column) {
        int life = game.GetPlayerProperty(row, Life_property);
        hardware.PrintSmallNumeric(x + col_margin, y, life, color, life > 99 ? 3 : 2);
      }
      else if (col == infect_column) {
        hardware.PrintSmallNumeric(x, y, game.GetPlayerProperty(row, Infect_property), color, 2);
      }
    }
  }
}

void Mainscreen::drawLayout(Hardware& hardware) {
  hardware.DrawScreen(mainlayout);
}

void Mainscreen::printManaPool(Game& game, Hardware& hardware) {
  int y = 0, x = 0;
  uint16_t color = BLACK;
  x = col_size + head_col_size + (4 * col_size) + col_margin + mana_head_col_size;
  for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
    y = (i * row_size) + row_margin;
    if (current_player == 0 && (current_property - 6) == i) {
      hardware.DrawBox(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
      color = WHITE;
    }
    hardware.PrintSmallNumeric(x, y, game.GetPlayerProperty(0, (PlayerProperties)(W_MANA_property + i)), color, 2);
  }
}