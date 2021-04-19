#ifndef SIMPLETWOPLAYER_INCLUDED
#define SIMPLETWOPLAYER_INCLUDED

#include "./resources/edh_twoplayersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleTwoPlayerEdhScreen : public DefaultPropertyNavigationScreen {
    private:
      int tick = 0;
      int symbol = 0;

    public:
      SimpleTwoPlayerEdhScreen() : DefaultPropertyNavigationScreen(14) { }

      virtual ScreenEnum GetNavigationId() { return SimpleTwoPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(Device& hardware, Game& game) {
        if (tick < 0 || tick > 2) tick = 0;

        processInputs(hardware, game);
        drawLayout(hardware);
        printPlayersProperties(hardware, game);
        printManaPool(hardware, game);

        if (hardware.IsMiddlePressed() == 1)
          return MainScreenEnum;

        return GetNavigationId();
      }

    protected:
      void updateNavigationPosition(int position) {
        if (position < 6) {
          current_player = 0;
          current_property = (PlayerProperties)(6 + (position % 6));
          return;
        }
        position -= 6;

        if (position == 1) {
          current_player = 0;
          current_property = Life_property;
          return;
        }
        position -= 1;

        int prop = (position / 3);
        current_property = prop > 0 ? (prop == 1 ? Commander_1_property : Commander_2_property) : Infect_property;
        current_player = position % 3;
        return;
      }

      void printPlayersProperties(Device& hardware, Game& game) {
        int life = 3, y = 0, x = 0;
        x = life < 100 ? 4 : 0;
        y = 10;
        uint16_t color = BLACK;

        if (current_player == 0 && current_property == Life_property) {
          hardware.DrawBox(x - 1, y - 1, 10, 10, color);
          color = WHITE;
        }
        hardware.PrintIntLarge(x, y, life, color, 2);
        color = BLACK;

        if (current_player == 1 && current_property == Life_property) {
          hardware.DrawBox(x - 1, y - 1, 10, 10, color);
          color = WHITE;
        }
        hardware.PrintIntLarge(life < 100 ? 60 : 36, 10, life, color, 2);
        color = BLACK;

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 2; col++, color = BLACK) {
            x = 29 + (col * 17);
            y = 4 + (row * 8);

            if (col == current_player && (current_property == row || (current_property == Infect_property && row == 2))) {
              hardware.DrawBox(x - 1, y - 1, 10, 10, color);
              color = WHITE;
            }

            if (row == 0) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(col, (PlayerProperties)(!col)), color, 2);
            }
            else if (row == 1) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(col, (PlayerProperties)(col)), color, 2);
            }
            else {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(col, Infect_property), color, 2);
            }
          }
        }
      }

      void drawLayout(Device& hardware) {
        hardware.DrawScreen(Resources::twoplayerlayout);
      }

      void printManaPool(Device& hardware, Game& game) {
        int y = 40, x = 0;
        uint16_t color = BLACK;
        for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
          x = 3 + (i * 14);
          hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(0, (PlayerProperties)(W_MANA_property + i)), BLACK, 2);
        }
      }
    };
  }
}
#endif
