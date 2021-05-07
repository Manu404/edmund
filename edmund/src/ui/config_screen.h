#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "screen.h"

namespace Edmund {
  namespace UI {
    class ConfigScreen : public IScreen
    {
      public:
        ConfigScreen() : IScreen() { }

        virtual ScreenEnum loop(const IInputDevice& input, const IOutputDevice& output, Game& game)
        {
          output.Print("L to reset", 7, 7);          
          
          if (input.IsLeftPressed())
            game.Reset();

          if (input.IsMiddlePressed() == 1)
            return BootScreenEnum;

          return GetNavigationId();
        }



        virtual void handleInputs(const IInputDevice& hardware, Game& game) { }

        virtual const ScreenEnum GetNavigationId() const { return ConfigScreenEnum; }
    };
  }
}
#endif
