#ifndef HOMESCREEN_INCLUDED
#define HOMESCREEN_INCLUDED

#include "screen.h"
#include "./resources/home_logo.h"

namespace Edmund {
  namespace UI {

    class HomeScreenMenuOption {
      public:
        HomeScreenMenuOption(ScreenEnum screen, const uint8_t* logo, int w, int h) {
          _logo = logo;
          _screen = screen;
          _h = h;
          _w = w;
        }
        const uint8_t* GetIcon() { return _logo; }
        ScreenEnum GetScreenEnum() { return _screen; }
        int GetWidth() { return _w; }
        int GetHeigt() { return _h; }
      private:
        const uint8_t* _logo;
        int _h, _w;
        ScreenEnum _screen;
    };

    class HomeScreen : public IScreen
    {
    private:
      int debug = -1;
      HomeScreenMenuOption* options[5];
    public:
      virtual ScreenEnum GetNavigationId() { return HomeMenuScreenEnum; }
      HomeScreen() : IScreen() {
        //int w = 52, h = 31;
        int w = 84, h = 48;
        options[0] = new HomeScreenMenuOption(HomeMenuScreenEnum, Resources::home_logo_icon, w, h);
        options[1] = new HomeScreenMenuOption(ConfigScreenEnum, Resources::config_icon, w, h);
        options[2] = new HomeScreenMenuOption(SimpleTwoPlayerEdhScreenEnum, Resources::two_player_icon, w, h);
        options[3] = new HomeScreenMenuOption(SimpleFourPlayerEdhScreenEnum, Resources::four_player_icon, w, h);
        options[4] = new HomeScreenMenuOption(CompleteFourPlayerEdhScreenEnum, Resources::four_player_icon, w, h);
      }

      int newSelection, currentSelection;
      int requestNavigation;
      long value, x_delta;
      int direction, currentFrame;
      int frameSkip = 5;

      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        processInputs(hardware, game);

        if (newSelection != currentSelection) {
          x_delta += (direction * (frameSkip * 6)) * ((currentFrame % frameSkip) == 0);
          x_delta = abs(x_delta) > 0 ? abs(x_delta) > 84 ? (84 * direction) : x_delta : 0;
          currentFrame += 1;
          drawOptionIcon(hardware, newSelection, (84 * (direction * -1)) + x_delta);
        }

        drawOptionIcon(hardware, currentSelection, x_delta);
        //drawOptionIcon(hardware, currentSelection, x_delta + direction);

        if (abs(x_delta) >= 84) {
          currentSelection = newSelection;
          x_delta = 0;
          currentFrame = 0;
        }
        
        if (newSelection == currentSelection)
          if (requestNavigation) 
            return options[currentSelection]->GetScreenEnum();

        hardware.PrintNumberSmall(40, 0, frameSkip, WHITE, 2);

        return GetNavigationId();
      }

      void drawOptionIcon(Device& hardware, int selection, int delta)
      {
        hardware.DrawLogo(delta, 0, options[selection]->GetWidth(), options[selection]->GetHeigt(), options[selection]->GetIcon());
      }

      virtual void processInputs(Device& hardware, Game& game) { 
        if (newSelection != currentSelection) return; // if in animation
        direction = hardware.GetEncoderDelta();
        frameSkip = hardware.GetPositionFromPot(10) + 1;
        value += direction;
        newSelection = (abs(value) % 4) + (value != 0);
        requestNavigation = hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed();
      }

    };
  }
}
#endif