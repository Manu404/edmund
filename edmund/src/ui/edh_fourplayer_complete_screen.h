#ifndef MAINSCREEN_INCLUDED
#define MAINSCREEN_INCLUDED

#include "screen.h"
#include "./resources/edh_fourplayercomplete_layout.h"

namespace Edmund {
  namespace UI {
    class CompleteFourPlayerEdhScreen : public DefaultPropertyNavigationScreen
    {

      public:
        CompleteFourPlayerEdhScreen() : DefaultPropertyNavigationScreen(25) { }

        virtual const ScreenEnum GetNavigationId() const { return CompleteFourPlayerEdhScreenEnum; }

        ScreenEnum loop(const IInputDevice& hardware, const IOutputDevice& output, Game& game) {
          handleInputs(hardware, game);
          drawLayout(output);
          printPlayersProperties(output, game);
          printManaPool(output, game);

          if (hardware.IsMiddlePressed())
            return HomeMenuScreenEnum;

          return GetNavigationId();
        }

      private:
        int debug = -1;

        const int col_size = 12;
        const int row_size = 8;
        const int row_margin = 2;
        const int col_margin = 2;
        const int head_col_size = 6;
        const int mana_head_col_size = 7;

    protected:
        void updateNavigationPosition(int position) {
          if (position < 6) {
            currentPlayer = 0;
            currentProperty = (PlayerProperties)(6 + (position % 6));
            return;
          }
          position -= 6;

          if (position < 4) {
            currentPlayer = position;
            currentProperty = Life_property;
            return;
          }
          position -= 4;

          if (position < 12) {
            currentPlayer = (position / 3);
            int target_player = (position % 3);
            currentProperty = (PlayerProperties)(target_player + (target_player >= currentPlayer));
            return;
          }

          position -= 12;
          currentPlayer = position;
          currentProperty = Infect_property;
        }

        void printPlayersProperties(const IOutputDevice& hardware, Game& game) {
          int y = 0, x = 0;
          int life_column = Life_property, infect_column = Infect_property;
          uint16_t color = BLACK;

          for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 6; col++, color = BLACK) {
              if (col == row && col < life_column) continue;

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

              // print selection box
              if (row == currentPlayer && col == currentProperty) {
                hardware.DrawBox(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
                color = WHITE;
              }

              // print player property
              if (col < life_column) {
                hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(row, (PlayerProperties)(col)), color, 2);
              }
              else if (col == life_column) {
                int life = game.GetPlayerPropertyValue(row, Life_property);
                hardware.PrintNumberSmall(x + col_margin, y, life, color, life > 99 ? 3 : 2);
              }
              else if (col == infect_column) {
                hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(row, Infect_property), color, 2);
              }
            }
          }
        }

        void drawLayout(const IOutputDevice& hardware) {
          hardware.DrawScreen(Resources::MainScreenLayout);
        }

        void printManaPool(const IOutputDevice& hardware, Game& game) {
          int y = 0, x = 0;
          uint16_t color = BLACK;
          x = col_size + head_col_size + (4 * col_size) + col_margin + mana_head_col_size;
          for (int i = 0; i < MANA_TYPE_COUNT; i++, color = BLACK) {
            y = (i * row_size) + row_margin;
            if (currentPlayer == 0 && (currentProperty - 6) == i) {
              hardware.DrawBox(MAX(x - col_margin, 0), (y - 1), (col_size + 1), (row_size - 1), color);
              color = WHITE;
            }
            hardware.PrintNumberSmall(x, y, game.GetPlayerPropertyValue(0, (PlayerProperties)(W_MANA_property + i)), color, 2);
          }
        }
    };
  }
}
#endif
