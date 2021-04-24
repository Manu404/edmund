#include "./screen_manager.h"
#include "./config_screen.h"
#include "./boot_screen.h"
#include "./edh_twoplayer_simple.h"
#include "./edh_fourplayer_simple.h"
#include "./edh_fourplayer_complete.h"
#include "./homemenu_screen.h"

namespace Edmund {

  ScreenManager::ScreenManager() {
    RegisterInstance(new ConfigScreen());
    RegisterInstance(new BootScreen());
    RegisterInstance(new CompleteFourPlayerEdhScreen());
    RegisterInstance(new SimpleFourPlayerEdhScreen());
    RegisterInstance(new SimpleTwoPlayerEdhScreen());
    RegisterInstance(new HomeScreen());
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

