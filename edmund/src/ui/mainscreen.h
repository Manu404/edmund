#ifndef MAINSCREEN_INCLUDED
#define MAINSCREEN_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"
#include "screen.h"

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

    int current_player;
    PlayerProperties current_property;

    void printManaPool(Game& game, Hardware& hardware);

    void printPlayersProperties(Hardware& hardware, Game& game);
    void drawLayout(Hardware& hardware);
    void updateNavigationPosition(int position);
    void processInputs(Hardware& hardware, Game& game);    
  public: 
    MainScreen();
    virtual ScreenEnum loop(Hardware& hardware, Game& game);
};
#endif
