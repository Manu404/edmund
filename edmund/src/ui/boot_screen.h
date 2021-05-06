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

      virtual ScreenEnum loop(const IInputDevice& hardware, const IOutputDevice& output, Game& game)
      {
        current = millis();
        ellapsed_ms += current - last_tick;
        last_tick = current;

        output.DrawScreen(Resources::BootLogo);

        if (hardware.IsMiddlePressed() == 1 || ellapsed_ms >= 1000)
          return HomeMenuScreenEnum;

        return GetNavigationId();
      }

      virtual void handleInputs(const IInputDevice& hardware, Game& game) { ; }

      virtual const ScreenEnum GetNavigationId() const { return BootScreenEnum; }
    };
  }
}
#endif
