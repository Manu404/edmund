#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "../hardware/device.h"
#include "../game.h"

namespace Edmund {
  namespace UI {
    enum ScreenEnum {
      MainScreenEnum = 1,
      ConfigScreenEnum = 2,
      BootScreenEnum = 3,
      SimpleFourPlayerEdhScreenEnum = 4
    };

    class IScreen
    {
      public:
        IScreen(int _propertyCount) {
          propertyCount = _propertyCount;
        }
        virtual ScreenEnum loop(Device& hardware, Game& game) = 0;
      protected:
        int current_player;
        int propertyCount;
        PlayerProperties current_property;

        void processInputs(Device& hardware, Game& game) {
          if (hardware.HasPotChanged())
            updateNavigationPosition(hardware.GetPositionFromPot(propertyCount));

          if (hardware.IsRightPressed() == 1)
            game.UpdatePlayerProperty(1, current_player, current_property);
          if (hardware.IsLeftPressed() == 1)
            game.UpdatePlayerProperty(-1, current_player, current_property);

          if (hardware.GetEncoderDelta() != 0)
            game.UpdatePlayerProperty(hardware.GetEncoderDelta(), current_player, current_property);

          if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
            hardware.SaveStateToSpiff(game.GetGameState());
        }

        virtual void updateNavigationPosition(int position) = 0;
    };
  }
}

#endif
