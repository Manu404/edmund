#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#define PLAYER_COUNT 4

namespace Edmund {
  #define PROPERTY_COUNT 6
  enum PlayerProperties {
    Commander_1_property = 0,
    Commander_2_property = 1,
    Commander_3_property = 2,
    Commander_x_property = 3,
    Life_property = 4,
    Infect_property = 5,
    W_MANA_property = 6,
    U_MANA_property = 7,
    R_MANA_property = 8,
    B_MANA_property = 9,
    G_MANA_property = 10,
    X_MANA_property = 11
  };

  class Player
  {
    private:
      int life;
      unsigned int commanderDamages[PLAYER_COUNT];
      unsigned int infect;

    public:
      Player() {
        life = 40;
        infect = 0;
        for (int i = 0; i < PLAYER_COUNT; i++)
          commanderDamages[i] = 0;
      }

      void ApplyDeltaToLife(int delta) {
        life += delta;
      }

      int GetLife() {
        return life;
      }

      void ApplyDeltaToCommanderDamages(int delta, byte target) {
        if (target < 0 || target > PLAYER_COUNT) return;
        if (delta < 0 && abs(delta) >= commanderDamages[target]) commanderDamages[target] = 0;
        else commanderDamages[target] += delta;
      }

      unsigned int GetCommanderDamages(byte target) {
        if ((target < 0 || target > PLAYER_COUNT)) return 0;
        return commanderDamages[target];
      }

      void ApplyDeltaToInfect(int delta) {
        if ((delta < 0 && abs(delta) >= infect)) 
          infect = 0;
        else 
          infect += delta;
      }

      unsigned int GetInfect() {
        return infect;
      }
  };
}
#endif
