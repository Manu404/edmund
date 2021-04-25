#ifndef SIMPLEFOURPLAYER_INCLUDED
#define SIMPLEFOURPLAYER_INCLUDED

#include "./resources/edh_fourplayersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleFourPlayerEdhScreen : public DefaultPropertyNavigationScreen
    {
    public:
      SimpleFourPlayerEdhScreen() : DefaultPropertyNavigationScreen(16) { }

      virtual ScreenEnum GetNavigationId() { return SimpleFourPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(Device& hardware, Game& game) {
        processInputs(hardware, game);

        drawLayout(hardware);
        printPlayersProperties(hardware, game);
        printManaPool(hardware, game);

        if (hardware.IsMiddlePressed())
          return HomeMenuScreenEnum;

        return GetNavigationId();
      }

    protected:
      void updateNavigationPosition(int position) {
        if (position < 6) {
          current_property = (PlayerProperties)(X_MANA_property - (position % 6));
          return;
        }
        position -= 6;

        if (position < 1) {
          current_player = position;
          current_property = Life_property;
          return;
        }
        position -= 1;

        if (position < 9) {
          int prop = position / 3;
          if (prop == 2) {
            current_player = (position % 3) + 1;
            current_property = Infect_property;
          }
          else if (prop == 1) {
            current_player = (position % 3) + 1;
            current_property = Commander_1_property;
          }
          else {
            current_player = 0;
            current_property = ((PlayerProperties)((position % 3) + 1));
          }
          return;
        }
      }

      void printPlayersProperties(Device& hardware, Game& game) {
        int y = 0, x = 0;
        uint16_t color = WHITE;

        int life = game.GetPlayerPropertyValue(0, Life_property);
        x = life < 100 ? 5 : 0;
        y = 10;
        if (current_player == 0 && current_property == Life_property)
          hardware.DrawBox(9, 22, 11, 2, WHITE);
        hardware.PrintNumberLarge(x, y, life, color, 2);

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 3; col++) {
            color = BLACK;
            x = 37 + (col * 12);
            y = 8 + (row * 7);

            if ((row == 0 && col + 1 == current_property)
            || (row == 1 && current_player == (col + 1) && current_property == Commander_1_property)
            || (row == 2 && current_player == (col + 1) && current_property == Infect_property)) {
              hardware.DrawBox(x - 1, y - 1, 12, 7, BLACK);
              color = WHITE;
            }

            if (row == 0) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(0, (PlayerProperties)(col + 1)), color, 2);
            }
            else if (row == 1) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(col + 1, Commander_1_property), color, 2);
            }
            else {
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(col + 1, Infect_property), color, 2);
            }
          }
        }
      }

      void drawLayout(Device& hardware) {
        hardware.DrawScreen(Resources::simple4PlayerLayout);
      }

      void printManaPool(Device& hardware, Game& game) {
        int y = 40, x = 0;
        uint16_t color = BLACK;
        for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
          x = 3 + (i * 14);
          if (current_player == 0 && (current_property - 6) == i) {
            hardware.DrawBox(x - 1, (y - 1), 11, 7, color);
            color = WHITE;
          }
          hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(0, (PlayerProperties)(W_MANA_property + i)), color, 2);
        }
      }
    };
  }
}
#endif
