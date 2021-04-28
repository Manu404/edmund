#pragma once
#ifndef MANA_INCLUDED
#define MANA_INCLUDED

namespace Edmund {
#define MANA_TYPE_COUNT 6
  enum ManaType {
    W_MANA = 0,
    U_MANA = 1,
    R_MANA = 2,
    B_MANA = 3,
    G_MANA = 4,
    X_MANA = 5
  };

  class ManaPoolState {
  private:
    unsigned int pool[MANA_TYPE_COUNT + 1];
  public:

    ManaPoolState() {
      Empty();
    }

    unsigned int GetManaPoolContent(ManaType type) {
      return pool[type];
    }

    void ApplyDeltaToManaPoolContent(ManaType type, int delta) {
      if (delta < 0 && abs(delta) >= pool[type]) pool[type] = 0;
      else pool[type] += delta;
    }

    void Empty() {
      for (byte i = 0; i < MANA_TYPE_COUNT; pool[i] = 0, i++);
    }
  };
}
#endif