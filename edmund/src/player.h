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
      int commanderDamages[PLAYER_COUNT];
      int infect;

    public:
      Player() {
        life = 40;
        infect = 0;
        for (int i = 0; i < PLAYER_COUNT; i++)
          commanderDamages[i] = 0;
      }

      void ApplyDeltaToLife(int delta) {
        if (delta > 1 || delta < -1 || (delta < 0 && life == 0)) return;
        life += delta;
      }

      int GetLife() {
        return life;
      }

      void ApplyDeltaToCommanderDamages(int delta, int target) {
        if (delta > 1 || delta < -1 || (delta < 0 && commanderDamages[target] == 0) || (target < 0 || target > PLAYER_COUNT)) return;
        commanderDamages[target] += delta;
      }

      int GetCommanderDamages(int target) {
        if ((target < 0 || target > PLAYER_COUNT)) return 0;
        return commanderDamages[target];
      }

      void ApplyDeltaToInfect(int delta) {
        if (delta > 1 || delta < -1 || (delta < 0 && infect == 0)) return;
        infect += delta;
      }

      int GetInfect() {
        return infect;
      }
  };
}
#endif
