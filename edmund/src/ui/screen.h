#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "../hardware/device.h"
#include "../game.h"

namespace Edmund {
  namespace UI {
    enum ScreenEnum {
      CompleteFourPlayerEdhScreenEnum = 1,
      ConfigScreenEnum = 2,
      BootScreenEnum = 3,
      SimpleFourPlayerEdhScreenEnum = 4,
      SimpleTwoPlayerEdhScreenEnum = 5,
      HomeMenuScreenEnum = 6
    };

    class IScreen
    {
      public:
        IScreen() {
        }
        virtual ScreenEnum loop(Device& hardware, Game& game) = 0;
        virtual ScreenEnum GetNavigationId() = 0;
      protected:
        virtual void processInputs(Device& hardware, Game& game) = 0;
    };

    class DefaultPropertyNavigationScreen : public IScreen {
      public:
        DefaultPropertyNavigationScreen(int _propertyCount) : IScreen() {
          propertyCount = _propertyCount;
        }
      protected:
        int readOnlySelection = 0;
        int current_player;
        int propertyCount;
        PlayerProperties current_property;

        void processInputs(Device& hardware, Game& game) {
          if (hardware.HasPotChanged())
            updateNavigationPosition(hardware.GetPositionFromPot(propertyCount));

          if (readOnlySelection) return;

          if (hardware.IsRightPressed() == 1)
            game.UpdatePlayerProperty(1, current_player, current_property);
          if (hardware.IsLeftPressed() == 1)
            game.UpdatePlayerProperty(-1, current_player, current_property);

          if (hardware.GetEncoderDelta() != 0)
            game.UpdatePlayerProperty(hardware.GetEncoderDelta(), current_player, current_property);

          //if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
          //  hardware.SaveStateToSpiff(game.GetGameState());
        }
        virtual void updateNavigationPosition(int position) = 0;
    };
  }
}

#endif
