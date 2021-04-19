#ifndef BOOTSCREEN_INCLUDED
#define BOOTSCREEN_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"
#include "./resources/bootscreen_logo.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class BootScreen : public IScreen
    {
    private:
      int tick = 0;
      int symbol = 0;
    public:
      BootScreen() {

      }
      virtual ScreenEnum loop(Hardware& hardware, Game& game)
      {
        if (tick == 20) tick = 0;

        tick += 1;
        hardware.DrawScreen(Resources::BootLogo);

        if (hardware.IsMiddlePressed() == 1 || tick == 20)
          return MainScreenEnum;
        return BootScreenEnum;
      }
    };
  }
}
#endif
