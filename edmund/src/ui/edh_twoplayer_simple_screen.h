#ifndef SIMPLETWOPLAYER_INCLUDED
#define SIMPLETWOPLAYER_INCLUDED

#include "./resources/edh_twoplayersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleTwoPlayerEdhScreen : public DefaultPropertyNavigationScreen {
    public:
      SimpleTwoPlayerEdhScreen() : DefaultPropertyNavigationScreen(14) { }

      virtual const ScreenEnum GetNavigationId() const { return SimpleTwoPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(const IInputDevice& input, const IOutputDevice& output, Game& game) {

        handleInputs(input, game);
        drawLayout(output);
        printPlayersProperties(output, game);
        printManaPool(output, game);

        if (input.IsMiddlePressed())
          return HomeMenuScreenEnum;

        return GetNavigationId();
      }

    protected:
      void updateNavigationPosition(int position) {
        readOnlySelection = 0;

        if (position < 6) {
          currentProperty = (PlayerProperties)(X_MANA_property - (position % 6));
          return;
        }
        position -= 6;

        if (position < 2) {
          currentPlayer = position;
          currentProperty = Life_property;
          return;
        }
        position -= 2;

        if (position < 6) {
          currentPlayer = position % 2;
          int prop = position / 2;
          currentProperty = prop < 2 ? ((PlayerProperties)(prop == 0 ? !currentPlayer : currentPlayer)) : Infect_property;
          readOnlySelection = prop == 1;
          return;
        }
      }

      void printPlayersProperties(const IOutputDevice& hardware, Game& game) {
        int y = 0, x = 0;
        uint16_t color = WHITE;

        for (int i = 0, y = 10; i < 2; i++)
        {
          int life = game.GetPlayerPropertyValue(i, Life_property);
          x = life < 100 ? 5 + (54 * i) : 0 + (53 * i);
          if (currentPlayer == i && currentProperty == Life_property)
            hardware.DrawBox(9 + (55 * i), 22, 11, 2, WHITE);
          hardware.PrintNumberLarge(x, y, life, color, 2);
        }

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 2; col++) {
            color = BLACK;
            x = 29 + (col * 17);
            y = 4 + (row * 8);

            if (col == currentPlayer) {
              if ((currentProperty == Infect_property && row == 2)
                || (currentProperty == (PlayerProperties)(col) && row == 1)
                || (currentProperty == (PlayerProperties)(!col) && row == 0))
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

      void drawLayout(const IOutputDevice& hardware) {
        hardware.DrawScreen(Resources::twoplayerlayout);
      }

      void printManaPool(const IOutputDevice& hardware, Game& game) {
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
