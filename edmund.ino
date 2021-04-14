#include "./hardware.h"
#include "./game.h"

int debug = -1;
Game game = Game();
Hardware hardware = Hardware();

void setup() {
  Serial.print(".");
  hardware.Initialize();
  game.state = hardware.LoadStateFromSpiff();
}

void loop() {  
  hardware.BeginFrame();

  if(hardware.HasPotChanged())
    game.UpdateCurrentPropertyFromPot(hardware.GetPositionFromPot(3 * 3));
    
  if(hardware.IsRightPressed() == 1)
    game.UpdateCurrentProperty(1);    
  if(hardware.IsLeftPressed() == 1)
    game.UpdateCurrentProperty(-1);
  if(hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
    hardware.SaveStateToSpiff(game.state);    
    
  if(hardware.IsDebugPressed() == 1)
    debug *= -1;
         
  hardware.PrintLine(game.GetOpponentLifeLine());
  hardware.PrintLine(game.GetCommanderDamages());
  hardware.PrintLine(game.GetReceivedCommanderDamages());
  
  if(debug == 1) {    
    hardware.PrintLine(hardware.GetDebugLine());
    hardware.PrintLine(game.GetCurrentPosition());
  }
  
  hardware.EndFrame();
  
  if(hardware.IsResetPressed() == 1)
    game = Game();

  Serial.print("."); 
  delay(20);
 }
