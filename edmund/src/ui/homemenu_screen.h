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

      int newSelection = 0;
      int lastSelection = 0;
      int requestNavigation = 0;
      long value, x_delta = 0;
      int direction;


      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        processInputs(hardware, game);

        if (newSelection != lastSelection) {
          x_delta += (direction * 5);
          drawLogo(hardware, (84 * (direction * -1)) + (x_delta), newSelection);
        }

        drawLogo(hardware, x_delta, lastSelection);

        if (abs(x_delta) >= 84) {
          lastSelection = newSelection;
          x_delta = 0;
        }
        
        if (newSelection == lastSelection)
          if (requestNavigation) {
            switch (newSelection) {
            case 1: return CompleteFourPlayerEdhScreenEnum;
            case 2: return SimpleTwoPlayerEdhScreenEnum;
            case 3: return ConfigScreenEnum;
            default: break;
            }
          }

        return GetNavigationId();
      }

      void drawLogo(Edmund::Device& hardware, int delta, int selection)
      {
        switch (selection) {
          case 0: hardware.DrawScreen(Resources::home_logo, delta); break;
          case 1: hardware.DrawScreen(Resources::four_player_icon,delta); break;
          case 2: hardware.DrawScreen(Resources::two_player_icon, delta); break;
          case 3: hardware.DrawScreen(Resources::config_icon, delta); break;
          default: break;
        }
      }

      virtual void processInputs(Device& hardware, Game& game) { 
        if (newSelection != lastSelection) return; // if in animation
        direction = hardware.GetEncoderDelta();
        value += direction;
        newSelection = (abs(value) % 3) + (value != 0);
        requestNavigation = hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed();
      }

      virtual ScreenEnum GetNavigationId() { return HomeMenuScreenEnum; }
    };
  }
}
#endif