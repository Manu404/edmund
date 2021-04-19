#include "./screenmanager.h"
#include "./configscreen.h"
#include "./bootscreen.h"
#include "./edh_twoplayer_simple.h"
#include "./edh_fourplayer_simple.h"
#include "./edh_fourplayer_complete.h"

namespace Edmund {

  ScreenManager::ScreenManager() {
    RegisterInstance(new MainScreen());
    RegisterInstance(new SimpleFourPlayerScreen());
    RegisterInstance(new ConfigScreen());
    RegisterInstance(new BootScreen());
    RegisterInstance(new SimpleTwoPlayerEdhScreen());
    current = screens[BootScreenEnum];
  }

  void ScreenManager::LoopCurrent(Device& hardware, Game& game) {
    NavigateTo(current->loop(hardware, game));
  }

  void ScreenManager::RegisterInstance(IScreen* screen) {
    screens[screen->GetNavigationId()] = screen;
  }

  void ScreenManager::NavigateTo(ScreenEnum screen) {
    current = screens[screen];
  }
}

