#include "gtest/gtest.h"
#include "Arduino.h"

#include "../src/game.h"

using ::testing::Return;
using namespace Edmund;


TEST(game, get_set_player_life_property) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    g->ApplyDeltaToPlayerProperty(i, Life_property, i + 1);
    EXPECT_EQ(40 + i + 1, g->GetPlayerPropertyValue(i, Life_property));
  }
}

TEST(game, get_set_player_infect_property) {
  Edmund::Game* g = new Edmund::Game(); 
  for (int i = 0; i < PLAYER_COUNT; i++) {
    g->ApplyDeltaToPlayerProperty(i, Infect_property, i + 1);
    EXPECT_EQ(i + 1, g->GetPlayerPropertyValue(i, Infect_property));
  }
}

TEST(game, get_set_player_cmdr_dmg_property) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    for (int target = 0; target < PLAYER_COUNT; target++)  {
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(target), i + 1);
      EXPECT_EQ(i + 1, g->GetPlayerPropertyValue(i, (PlayerProperties)(target)));
    }
  }
}

TEST(game, get_set_mana_property_single_player) {
  Edmund::Game* g = new Edmund::Game();
  for (int mana = 0; mana < MANA_TYPE_COUNT; mana++) {
    g->ApplyDeltaToPlayerProperty(0, (PlayerProperties)(W_MANA_property + mana), 1);
    EXPECT_EQ(1, g->GetPlayerPropertyValue(0, (PlayerProperties)(W_MANA_property + mana)));
  }
}

TEST(game, get_set_mana_property_all_player) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++) {
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(W_MANA_property + mana), i + 1);
      EXPECT_EQ(i + 1, g->GetPlayerPropertyValue(i, (PlayerProperties)(W_MANA_property + mana)));
    }
  }
}

TEST(game, get_player_count) {
  Edmund::Game* g = new Edmund::Game();
  EXPECT_EQ(4, g->GetPlayerCount());
}

TEST(game, get_property_count) {
  Edmund::Game* g = new Edmund::Game();
  EXPECT_EQ(6, g->GetPropertyCount());
}

TEST(game, get_manatype_count) {
  Edmund::Game* g = new Edmund::Game();
  EXPECT_EQ(6, g->GetManaTypeCount());
}

TEST(game, reset) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    g->ApplyDeltaToPlayerProperty(i, Infect_property, i + 1);
    g->ApplyDeltaToPlayerProperty(i, Life_property, i + 1);
    for (int target = 0; target < PLAYER_COUNT; target++)
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(target), i + 1);
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++)
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(W_MANA_property + mana), i + 1);
  }
  g->Reset();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    EXPECT_EQ(40, g->GetPlayerPropertyValue(i, Life_property));
    EXPECT_EQ(0, g->GetPlayerPropertyValue(i, Infect_property));
    for (int target = 0; target < PLAYER_COUNT; target++)
      EXPECT_EQ(0, g->GetPlayerPropertyValue(i, (PlayerProperties)(target)));
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++)
      EXPECT_EQ(0, g->GetPlayerPropertyValue(i, (PlayerProperties)(W_MANA_property + mana)));
  }
}