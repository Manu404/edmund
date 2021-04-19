#include "./screenmanager.h"
#include "./mainscreen.h"
#include "./configscreen.h"
#include "./bootscreen.h"

namespace UI {
  MainScreen _msInstance = MainScreen();
  ConfigScreen _cfInstance = ConfigScreen();
  BootScreen _btInstance = BootScreen();

  ScreenManager::ScreenManager() {
    current = &_btInstance;
  }

  void ScreenManager::loopCurrent(Hardware& hardware, Game& game) {
    NavigateTo(current->loop(hardware, game));
  }

  void ScreenManager::NavigateTo(ScreenEnum screen) {
    switch (screen) {
    case MainScreenEnum: current = &_msInstance; break;
    case ConfigScreenEnum: current = &_cfInstance; break;
    case BootScreenEnum: current = &_btInstance; break;
    default: break;
    }
  }
}
