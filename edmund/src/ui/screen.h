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
        IScreen() { }
        virtual ScreenEnum loop(const Device& hardware, Game& game) = 0;
        virtual const ScreenEnum GetNavigationId() const = 0;
      protected:
        virtual void handleInputs(const Device& hardware, Game& game) = 0;
    };

    class DefaultPropertyNavigationScreen : public IScreen {
      public:
        DefaultPropertyNavigationScreen(int _propertyCount) : IScreen(), propertyCount(_propertyCount) { }
      protected:
        bool readOnlySelection = false;
        byte currentPlayer;
        byte propertyCount;
        PlayerProperties currentProperty;

        virtual void updateNavigationPosition(int position) = 0;

        void handleInputs(const Device& hardware, Game& game) {
          if (hardware.HasPotChanged())
            updateNavigationPosition(hardware.GetPositionFromPot(propertyCount));

          if (readOnlySelection) return;

          if (hardware.GetEncoderDelta() != 0)
            game.ApplyDeltaToPlayerProperty(currentPlayer, currentProperty, hardware.GetEncoderDelta());

          if (hardware.IsLeftPressed())
            game.EmptyManaPool();
        }
    };
  }
}

#endif
