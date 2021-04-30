#ifndef HOMESCREEN_INCLUDED
#define HOMESCREEN_INCLUDED

#include "screen.h"
#include "./resources/home_logo.h"

namespace Edmund {
  namespace UI {

    class HomeScreenMenuOption {
      public:
        HomeScreenMenuOption(const ScreenEnum screen, const String caption, const uint8_t* logo, const int w, const int h) 
          : _icon(logo), _screen(screen), _h(h), _w(w), _caption(caption) { }
        const uint8_t* GetIcon() { return _icon; }
        const ScreenEnum GetScreenEnum() { return _screen; }
        const int GetIconWidth() { return _w; }
        const int GetIconHeight() { return _h; }
        const String GetCaption() { return _caption; }
      private:
        const int _h, _w;
        const uint8_t* _icon;
        const ScreenEnum _screen;
        const String _caption;
    };

    class HomeScreen : public IScreen
    {
    private:
      HomeScreenMenuOption* options[6];
      int newSelection, currentSelection;
      bool requestNavigation;
      long rotaryValue, x_delta;
      int direction, currentFrame;
      byte frameSkip = 1;
      int screenWidth = 0;
      byte optionCount = 0;

    public:
      HomeScreen() : IScreen() {
        //int w = 52, h = 31;
        int w = 84, h = 48;
        options[0] = new HomeScreenMenuOption(HomeMenuScreenEnum, "", Resources::home_logo_icon, w, h);
        options[1] = new HomeScreenMenuOption(ConfigScreenEnum, "Configuration", Resources::config_icon, w, h);
        options[2] = new HomeScreenMenuOption(SimpleTwoPlayerEdhScreenEnum, "2 pl. (basic)", Resources::two_player_icon, w, h);
        options[3] = new HomeScreenMenuOption(SimpleFourPlayerEdhScreenEnum, "4 pl. (basic)", Resources::four_player_icon, w, h);
        options[4] = new HomeScreenMenuOption(CompleteFourPlayerEdhScreenEnum, "4 pl. (full)", Resources::four_player_icon, w, h);
        options[5] = new HomeScreenMenuOption(ConfigScreenEnum, "Diagnostic", Resources::diag_icon, w, h);
        optionCount = (sizeof(options) / sizeof(HomeScreenMenuOption*)) - 1;
      }

      virtual const ScreenEnum GetNavigationId() const { return HomeMenuScreenEnum; }

      virtual ScreenEnum loop(const Device& hardware, Game& game)
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
        return GetNavigationId();
      }

      void drawOptionIcon(const Device& hardware, int selection, int delta)
      {
        hardware.DrawLogo(delta, 0, options[selection]->GetIconWidth(), options[selection]->GetIconHeight(), options[selection]->GetIcon());
        hardware.PrintLineCentered(options[selection]->GetCaption(), (screenWidth / 2) + delta, 45, WHITE);
      }

      virtual void processInputs(const Device& hardware, Game& game) {
        if (newSelection != currentSelection) return;
        direction = hardware.GetEncoderDelta();
        //frameSkip = hardware.GetPositionFromPot(10) + 1;
        rotaryValue += direction;
        newSelection = (abs(rotaryValue) % optionCount) + (rotaryValue != 0);
        requestNavigation = hardware.IsMiddlePressed() || hardware.IsRotarySwitchPressed();
      }
    };
  }
}
#endif