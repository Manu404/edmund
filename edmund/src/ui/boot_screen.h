#ifndef BOOTSCREEN_INCLUDED
#define BOOTSCREEN_INCLUDED

#include "./resources/bootscreen_logo.h"
#include "./screen.h"

namespace Edmund {
  namespace UI {
    class BootScreen : public IScreen
    {
    private:
      unsigned long ellapsed_ms = 0, last_tick = 0, current = 0;
    public:
      BootScreen() : IScreen() { }

      virtual ScreenEnum loop(const Device& hardware, Game& game)
      {
        //if (ellapsed_ms < 0 || ellapsed_ms > 1000) ellapsed_ms = 0;

        current = millis();
        ellapsed_ms += current - last_tick;
        last_tick = current;

        hardware.DrawScreen(Resources::BootLogo);

        if (hardware.IsMiddlePressed() == 1 || ellapsed_ms >= 1000)
          return HomeMenuScreenEnum;

        return GetNavigationId();
      }

      virtual void processInputs(const Device& hardware, Game& game) { ; }

      virtual ScreenEnum GetNavigationId() { return BootScreenEnum; }
    };
  }
}
#endif
