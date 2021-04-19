#include "./screenmanager.h"
#include "./mainscreen.h"
#include "./configscreen.h"
#include "./bootscreen.h"
#include "./simple4playerscreen.h"

namespace Edmund {

  ScreenManager::ScreenManager() {
    RegisterInstance(new MainScreen());
    RegisterInstance(new SimpleFourPlayerScreen());
    RegisterInstance(new ConfigScreen());
    RegisterInstance(new BootScreen());
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

