#include "./screen_manager.h"
#include "./config_screen.h"
#include "./boot_screen.h"
#include "./edh_twoplayer_simple_screen.h"
#include "./edh_fourplayer_simple_screen.h"
#include "./edh_fourplayer_complete_screen.h"
#include "./homemenu_screen.h"

namespace Edmund {

  ScreenManager::ScreenManager() {
    RegisterInstance(std::unique_ptr<IScreen>(new ConfigScreen()));
    RegisterInstance(std::unique_ptr<IScreen>(new BootScreen()));
    RegisterInstance(std::unique_ptr<IScreen>(new CompleteFourPlayerEdhScreen()));
    RegisterInstance(std::unique_ptr<IScreen>(new SimpleFourPlayerEdhScreen()));
    RegisterInstance(std::unique_ptr<IScreen>(new SimpleTwoPlayerEdhScreen()));
    RegisterInstance(std::unique_ptr<IScreen>(new HomeScreen()));
  }

  void ScreenManager::LoopCurrent(const Device& hardware, const IOutputDevice& output, Game& game) {
    NavigateTo(screens[current]->loop(hardware, output, game));
  }

  void ScreenManager::RegisterInstance(std::unique_ptr<IScreen> screen) {
    ScreenEnum target = screen->GetNavigationId();
    screens[screen->GetNavigationId()] = std::move(screen);
  }

  void ScreenManager::NavigateTo(ScreenEnum screen) {
    current = screen;
  }
}

