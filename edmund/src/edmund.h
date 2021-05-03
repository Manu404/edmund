#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./hardware/device.h"
#include "./ui/screen_manager.h"
#include "./game.h"
#include "./version.h"

#include <memory>

namespace Edmund {
  class EntryPoint {
  private:
    bool debug = false;
    std::unique_ptr<Game> game;
    std::unique_ptr<Device> device;;
    std::unique_ptr<ScreenManager> screenManager;
    unsigned long lastFrameDuration = 0, lastFrame = 0, currentFrame = 0;

  public:
    EntryPoint() {
      game = std::unique_ptr<Game>(new Game());
      device = std::unique_ptr<Device>(new Device());
      screenManager = std::unique_ptr<ScreenManager>(new ScreenManager());
    }

    void loop() {
      device->BeginFrame();
            
      screenManager->LoopCurrent(*device, *device->GetOutput(), *game);

      game->RefreshEllapsedTime();
      
      if (debug)  
        displayDebug(*device->GetOutput());
      
      device->EndFrame(game->GetGameState());
    }

    void setup() {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiffs());
      screenManager->NavigateTo(HomeMenuScreenEnum);
      Serial.println("setup");
      Serial.println(EDMUND_VERSION);
    }

    void displayDebug(IOutputDevice& hardware) {
      currentFrame = millis();
      lastFrameDuration = currentFrame - lastFrame;
      lastFrame = currentFrame;
      hardware.DrawBox(0, 0, 20, 6, BLACK);
      hardware.PrintNumberSmall(0, 0, lastFrameDuration, WHITE, 3);
      hardware.PrintNumberSmall(10, 0, round(1000 / (lastFrameDuration != 0 ? lastFrameDuration : 1)), WHITE, 3);
    }
  };
}
#endif
