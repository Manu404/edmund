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

      virtual const ScreenEnum GetNavigationId() const { return SimpleFourPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(const Device& hardware, Game& game) {
        handleInputs(hardware, game);

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
          currentProperty = (PlayerProperties)(X_MANA_property - (position % 6));
          return;
        }
        position -= 6;

        if (position < 1) {
          currentPlayer = position;
          currentProperty = Life_property;
          return;
        }
        position -= 1;

        if (position < 9) {
          int prop = position / 3;
          if (prop == 2) {
            currentPlayer = (position % 3) + 1;
            currentProperty = Infect_property;
          }
          else if (prop == 1) {
            currentPlayer = (position % 3) + 1;
            currentProperty = Commander_1_property;
          }
          else {
            currentPlayer = 0;
            currentProperty = ((PlayerProperties)((position % 3) + 1));
          }
          return;
        }
      }

      void printPlayersProperties(const Device& hardware, Game& game) {
        int y = 0, x = 0;
        uint16_t color = WHITE;

        int life = game.GetPlayerPropertyValue(0, Life_property);
        x = life < 100 ? 5 : 0;
        y = 10;
        if (currentPlayer == 0 && currentProperty == Life_property)
          hardware.DrawBox(9, 22, 11, 2, WHITE);
        hardware.PrintNumberLarge(x, y, life, color, 2);

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 3; col++) {
            color = BLACK;
            x = 37 + (col * 12);
            y = 8 + (row * 7);

            if ((row == 0 && col + 1 == currentProperty)
            || (row == 1 && currentPlayer == (col + 1) && currentProperty == Commander_1_property)
            || (row == 2 && currentPlayer == (col + 1) && currentProperty == Infect_property)) {
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

      void drawLayout(const Device& hardware) {
        hardware.DrawScreen(Resources::simple4PlayerLayout);
      }

      void printManaPool(const Device& hardware, Game& game) {
        int y = 40, x = 0;
        uint16_t color = BLACK;
        for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
          x = 3 + (i * 14);
          if (currentPlayer == 0 && (currentProperty - 6) == i) {
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
