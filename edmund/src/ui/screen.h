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
        virtual ScreenEnum loop(const IInputDevice& input, const IOutputDevice& output, Game& game) = 0;
        virtual const ScreenEnum GetNavigationId() const = 0;
      protected:
        virtual void handleInputs(const IInputDevice& input, Game& game) = 0;
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

        void handleInputs(const IInputDevice& input, Game& game) {
          if (input.HasPotChanged())
            updateNavigationPosition(input.GetPositionFromPot(propertyCount));

          if (readOnlySelection) return;

          if (input.GetEncoderDelta() != 0)
            game.ApplyDeltaToPlayerProperty(currentPlayer, currentProperty, input.GetEncoderDelta());

          if (input.IsLeftPressed())
            game.EmptyManaPools();
        }
    };
  }
}

#endif
