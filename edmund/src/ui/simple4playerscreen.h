#ifndef SIMPLEFOURPLAYER_INCLUDED
#define SIMPLEFOURPLAYER_INCLUDED

#include "./resources/bootscreen_logo.h"
#include "./resources/4playersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleFourPlayerScreen : public IScreen
    {
    private:
      int tick = 0;
      int symbol = 0;
    public:
      SimpleFourPlayerScreen() : IScreen(15) { }

      virtual ScreenEnum GetNavigationId() { return SimpleFourPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        if (tick < 0 || tick > 2) tick = 0;

        drawLayout(hardware);
        printPlayersProperties(hardware, game);
        printManaPool(hardware, game);

        if (hardware.IsMiddlePressed() == 1)
          return MainScreenEnum;

        return GetNavigationId();
      }

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
        hardware.PrintIntLarge(life < 100 ? 4 : 0, 10, life, 2);

        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 3; col++) {
            x = 37 + (col * 11) + (col > 0);
            y = 8 + (row * 7);
            if (row == 0) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(0, (PlayerProperties)(col)), BLACK, 2);
            }
            else if (row == 1) {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(row + 1, Commander_1_property), BLACK, 2);
            }
            else {
              hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(row + 1, Infect_property), BLACK, 2);
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
          hardware.PrintNumberSmall(x, y, game.GetPlayerProperty(0, (PlayerProperties)(W_MANA_property + i)), BLACK, 2);
        }
      }
    };
  }
}
#endif
