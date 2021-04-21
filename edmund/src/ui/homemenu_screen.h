#ifndef HOMESCREEN_INCLUDED
#define HOMESCREEN_INCLUDED

#include "screen.h"
#include "./resources/home_logo.h"

namespace Edmund {
  namespace UI {

    class HomeScreenMenuOption {
      public:
        HomeScreenMenuOption(ScreenEnum screen, String caption, const uint8_t* logo, int w, int h) {
          _logo = logo;
          _screen = screen;
          _h = h;
          _w = w;
          _caption = caption;
        }
        const uint8_t* GetIcon() { return _logo; }
        ScreenEnum GetScreenEnum() { return _screen; }
        int GetWidth() { return _w; }
        int GetHeigt() { return _h; }
        String GetCaption() { return _caption; }
      private:
        const uint8_t* _logo;
        int _h, _w;
        ScreenEnum _screen;
        String _caption;
    };

    class HomeScreen : public IScreen
    {
    private:
      int debug = 0;
      HomeScreenMenuOption* options[5];
      int newSelection, currentSelection;
      int requestNavigation;
      long value, x_delta;
      int direction, currentFrame;
      int frameSkip = 3;
      int screenWidth = 0;
      int optionCount = 0;

    public:
      virtual ScreenEnum GetNavigationId() { return HomeMenuScreenEnum; }
      HomeScreen() : IScreen() {
        //int w = 52, h = 31;
        int w = 84, h = 48;
        options[0] = new HomeScreenMenuOption(HomeMenuScreenEnum, "", Resources::home_logo_icon, w, h);
        options[1] = new HomeScreenMenuOption(ConfigScreenEnum, "Configuration", Resources::config_icon, w, h);
        options[2] = new HomeScreenMenuOption(SimpleTwoPlayerEdhScreenEnum, "2 pl. (basic)", Resources::two_player_icon, w, h);
        options[3] = new HomeScreenMenuOption(SimpleFourPlayerEdhScreenEnum, "4 pl. (basic)", Resources::four_player_icon, w, h);
        options[4] = new HomeScreenMenuOption(CompleteFourPlayerEdhScreenEnum, "4 pl. (full)", Resources::four_player_icon, w, h);
        optionCount = (sizeof(options) / sizeof(HomeScreenMenuOption*)) - 1;
      }

      virtual ScreenEnum loop(Device& hardware, Game& game)
      {
        processInputs(hardware, game);

        if (screenWidth == 0) screenWidth = hardware.GetScreenWidth();

        if (newSelection != currentSelection) {
          x_delta += (direction * (frameSkip * 6)) * ((currentFrame % frameSkip) == 0);
          x_delta = abs(x_delta) > 0 ? abs(x_delta) > screenWidth ? (screenWidth * direction) : x_delta : 0;
          currentFrame += 1;
          drawOptionIcon(hardware, newSelection, (screenWidth * (direction * -1)) + x_delta);
        }

        drawOptionIcon(hardware, currentSelection, x_delta);

        if (abs(x_delta) >= screenWidth) {
          currentSelection = newSelection;
          x_delta = 0;
          currentFrame = 0;
        }
        
        if (newSelection == currentSelection)
          if (requestNavigation) 
            return options[currentSelection]->GetScreenEnum();

        //hardware.PrintNumberSmall(40, 0, frameSkip, WHITE, 2);

        return GetNavigationId();
      }

      void drawOptionIcon(Device& hardware, int selection, int delta)
      {
        hardware.DrawLogo(delta, 0, options[selection]->GetWidth(), options[selection]->GetHeigt(), options[selection]->GetIcon());
        hardware.DrawCentreString(options[selection]->GetCaption(), (screenWidth / 2) + delta, 45);
      }

      virtual void processInputs(Device& hardware, Game& game) { 
        if (newSelection != currentSelection) return;
        direction = hardware.GetEncoderDelta();
        frameSkip = hardware.GetPositionFromPot(10) + 1;
        value += direction;
        newSelection = (abs(value) % optionCount) + (value != 0);
        requestNavigation = hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed();
      }

    };
  }
}
#endif