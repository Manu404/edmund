#ifndef SIMPLEFOURPLAYER_INCLUDED
#define SIMPLEFOURPLAYER_INCLUDED

#include "./resources/edh_fourplayersimple_layout.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class SimpleFourPlayerEdhScreen : public DefaultPropertyNavigationScreen
    {
    private:
      int tick = 0;
      int symbol = 0;

    public:
      SimpleFourPlayerEdhScreen() : DefaultPropertyNavigationScreen(14) { }

      virtual ScreenEnum GetNavigationId() { return SimpleFourPlayerEdhScreenEnum; }

      virtual ScreenEnum loop(Device& hardware, Game& game) {
        if (tick < 0 || tick > 2) tick = 0;

        drawLayout(hardware);
        printPlayersProperties(hardware, game);
        printManaPool(hardware, game);

        if (hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed())
          return HomeMenuScreenEnum;

        return GetNavigationId();
      }

    protected:
      void updateNavigationPosition(int position) {
        //if (position <= 5) {
        //  current_player = 0;
        //  current_property = (PlayerProperties)(6 + (position % 6));
        //  return;
        //}
        //position -= 5;

        //if (position == 1) {
        //  current_player = 0;
        //  current_property = Life_property;
        //  return;
        //}
        //position -= 1;

        //if (position <= 5) {
        //  current_player = position % 2 == 1;
        //  int prop = (position / 2);
        //  current_property = prop == 2 ? (PlayerProperties)(!current_player) : Infect_property;
        //  return;
        //}
        return;
      }

      void printPlayersProperties(Device& hardware, Game& game) {
        int life = 3, y = 0, x = 0;
        hardware.PrintIntLarge(life < 100 ? 4 : 0, 10, life, BLACK, 2);

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