#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "screen.h"
#include <map>
#include <memory>

namespace Edmund {
  using namespace UI;
  class ScreenManager {
    public:
      ScreenManager();
      void LoopCurrent(const Device& hardware, const IOutputDevice& output, Game& game);
      void NavigateTo(ScreenEnum screen);
      void RegisterInstance(std::unique_ptr<IScreen> screen);
    private:
      ScreenEnum current;
      std::map<ScreenEnum, std::unique_ptr<IScreen>> screens;
  };
}
#endif
