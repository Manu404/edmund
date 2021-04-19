#ifndef BOOTSCREEN_INCLUDED
#define BOOTSCREEN_INCLUDED

#include "./resources/bootscreen_logo.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class BootScreen : public IScreen
    {
    private:
      int ellapsed_ms = 0, last_tick = 0, current = 0;
    public:
      BootScreen() : IScreen(15) { }

      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        //if (ellapsed_ms < 0 || ellapsed_ms > 1000) ellapsed_ms = 0;

        current = millis();
        ellapsed_ms += current - last_tick;
        last_tick = current;

        hardware.DrawScreen(Resources::BootLogo);

        if (hardware.IsMiddlePressed() == 1 || ellapsed_ms >= 1000)
          return SimpleTwoPlayerEdhScreenEnum;

        return GetNavigationId();
      }

      virtual void updateNavigationPosition(int position) { }

      virtual ScreenEnum GetNavigationId() { return BootScreenEnum; }
    };
  }
}
#endif
