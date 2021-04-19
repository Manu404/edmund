#ifndef MAINSCREEN_INCLUDED
#define MAINSCREEN_INCLUDED

#include "screen.h"

namespace Edmund {
  namespace UI {
    class MainScreen : public IScreen 
    {
      private:
        int debug = -1;

        const int col_size = 12;
        const int row_size = 8;
        const int row_margin = 2;
        const int col_margin = 2;
        const int head_col_size = 6;
        const int mana_head_col_size = 7;

        void printPlayersProperties(Device& hardware, Game& game);
        void printManaPool(Device& hardware, Game& game);
        void drawLayout(Device& hardware);

        virtual void updateNavigationPosition(int position);

        virtual ScreenEnum GetNavigationId() { return MainScreenEnum; }

      public:
        MainScreen() : IScreen(24) { }
        virtual ScreenEnum loop(Device& hardware, Game& game);
    };
  }
}
#endif
