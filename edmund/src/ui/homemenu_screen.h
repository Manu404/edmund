#ifndef HOMESCREEN_INCLUDED
#define HOMESCREEN_INCLUDED

#include "screen.h"
#include "./resources/home_logo.h"

namespace Edmund {
  namespace UI {
    class HomeScreen : public IScreen
    {
    private:
      int debug = -1;
    public:
      HomeScreen() : IScreen() { }

      int currentSelection = 0;
      int requestNavigation = 0;
      int value;
      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        processInputs(hardware, game);

        switch (currentSelection) {
          case 0: hardware.DrawScreen(Resources::four_player_icon); break;
          case 1: hardware.DrawScreen(Resources::two_player_icon); break;
          case 2: hardware.DrawScreen(Resources::config_icon); break;
          default: break;
        }

        if (requestNavigation) {
          switch (currentSelection) {
          case 0: return CompleteFourPlayerEdhScreenEnum;
          case 1: return SimpleTwoPlayerEdhScreenEnum;
          case 2: return ConfigScreenEnum;
          default: break;
          }
        }

        return GetNavigationId();
      }

      virtual void processInputs(Device& hardware, Game& game) { 
        value += hardware.GetEncoderDelta();
        currentSelection = abs(value) % 3;
        requestNavigation = hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed();
      }

      virtual ScreenEnum GetNavigationId() { return HomeMenuScreenEnum; }
    };
  }
}
#endif