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
        virtual ScreenEnum loop(const Device& hardware, Game& game) = 0;
        virtual ScreenEnum GetNavigationId() = 0;
      protected:
        virtual void processInputs(const Device& hardware, Game& game) = 0;
    };

    class DefaultPropertyNavigationScreen : public IScreen {
      public:
        DefaultPropertyNavigationScreen(int _propertyCount) : IScreen() {
          propertyCount = _propertyCount;
        }
      protected:
        bool readOnlySelection = false;
        int current_player;
        int propertyCount;
        PlayerProperties current_property;

        void processInputs(const Device& hardware, Game& game) {
          if (hardware.HasPotChanged())
            updateNavigationPosition(hardware.GetPositionFromPot(propertyCount));

          if (readOnlySelection) return;

          //if (hardware.IsRightPressed() == 1)
          //  game.UpdatePlayerPropertyValue(current_player, current_property, 1);
          //if (hardware.IsLeftPressed() == 1)
          //  game.UpdatePlayerPropertyValue(current_player, current_property, -1);

          if (hardware.GetEncoderDelta() != 0)
            game.ApplyDeltaToPlayerProperty(current_player, current_property, hardware.GetEncoderDelta());

          if (hardware.IsLeftPressed())
            game.EmptyManaPool();

          //if (hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
          //  hardware.SaveStateToSpiff(game.GetGameState());
        }
        virtual void updateNavigationPosition(int position) = 0;
    };
  }
}

#endif
