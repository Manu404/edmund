#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Player
{
  public:
    int Life;
    int CommanderDamages;
    int ReceivedCommanderDamages;
    int Infect;
    
    Player(){
      Life = 40;
      CommanderDamages = 0;
      ReceivedCommanderDamages = 0;
      Infect = 0;      
    }

    void ApplyDeltaToLife(int delta){
      if(delta < 0 && Life == 0) return;
      Life += delta;
    }

    void ApplyDeltaToCommanderDamages(int delta){
      if(delta < 0 && CommanderDamages == 0) return;
      CommanderDamages += delta;      
    }

    void ApplyDeltaToReceivedCommanderDamages(int delta){
      if(delta < 0 && ReceivedCommanderDamages == 0) return;
      ReceivedCommanderDamages += delta;      
    }

    void ApplyDeltaToInfect(int delta){
      if(delta < 0 && Infect == 0) return;
      Infect += delta;
      
    }
};

#endif
