#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#define PLAYER_COUNT 4
#define PROPERTY_COUNT 5

class Player
{
  public:
    int Life;
    int CommanderDamages[PLAYER_COUNT];
    int Infect;
    
    Player(){
      Life = 40;
      Infect = 0;   
      for (int i = 0; i < PLAYER_COUNT; i++)
        CommanderDamages[i] = i;
    }

    void ApplyDeltaToLife(int delta){
      if(delta < 0 && Life == 0) return;
      Life += delta;
    }

    void ApplyDeltaToCommanderDamages(int delta){
      if(delta < 0 && CommanderDamages == 0) return;
      CommanderDamages[0] += delta;      
    }

    void ApplyDeltaToReceivedCommanderDamages(int delta){
      if(delta < 0 && CommanderDamages == 0) return;
      CommanderDamages[0] += delta;
    }

    void ApplyDeltaToInfect(int delta){
      if(delta < 0 && Infect == 0) return;
      Infect += delta;      
    }
};

#endif
