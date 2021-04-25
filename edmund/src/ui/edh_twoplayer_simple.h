#ifndef SIMPLETWOPLAYER_INCLUDED
#define SIMPLETWOPLAYER_INCLUDED

#include "./resources/edh_twoplayersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleTwoPlayerEdhScreen : public DefaultPropertyNavigationScreen {
    public:
      SimpleTwoPlayerEdhScreen() : DefaultPropertyNavigationScreen(14) { }
      virtual ScreenEnum GetNavigationId() { return SimpleTwoPlayerEdhScreenEnum; }
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
        readOnlySelection = 0;

        if (position < 6) {
          current_property = (PlayerProperties)(X_MANA_property - (position % 6));
          return;
        }
        position -= 6;

        if (position < 2) {
          current_player = position;
          current_property = Life_property;
          return;
        }
        position -= 2;

        if (position < 6) {
          current_player = position % 2;
          int prop = position / 2;
          current_property = prop < 2 ? ((PlayerProperties)(prop == 0 ? !current_player : current_player)) : Infect_property;
          readOnlySelection = prop == 1;
          return;
        }
      }

      void printPlayersProperties(Device& hardware, Game& game) {
        int y = 0, x = 0;
        uint16_t color = WHITE;

        for (int i = 0, y = 10; i < 2; i++)
        {
          int life = game.GetPlayerPropertyValue(i, Life_property);
          x = life < 100 ? 5 + (54 * i) : 0 + (53 * i);
          if (current_player == i && current_property == Life_property)
            hardware.DrawBox(9 + (55 * i), 22, 11, 2, WHITE);
          hardware.PrintNumberLarge(x, y, life, color, 2);
        }

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 2; col++) {
            color = BLACK;
            x = 29 + (col * 17);
            y = 4 + (row * 8);

            if (col == current_player) {
              if ((current_property == Infect_property && row == 2)
                || (current_property == (PlayerProperties)(col) && row == 1)
                || (current_property == (PlayerProperties)(!col) && row == 0))
              {
                hardware.DrawBox(x - 1, y - 1, 11, 7, BLACK);
                color = WHITE;
              }
            }

            if (row == 0)
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(col, (PlayerProperties)(!col)), color, 2);
            else if (row == 1)
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(!col, (PlayerProperties)(col)), color, 2);
            else
              hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(col, Infect_property), color, 2);
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
