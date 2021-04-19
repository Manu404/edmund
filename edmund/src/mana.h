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
    int pool[MANA_TYPE_COUNT];
  public:

    ManaPoolState() {
      Empty();
    }

    int GetManaPoolContent(ManaType type) {
      return pool[type];
    }

    int ApplyDeltaToManaPoolContent(ManaType type, int delta) {
      pool[type] += delta;
      if (pool[type] < 0) pool[type] = 0;
    }

    int* GetManaPoolContent() {
      return pool;
    }

    void Empty() {
      for (int i = 0; i < MANA_TYPE_COUNT; pool[i] = 0, i++);
    }
  };
}
#endif