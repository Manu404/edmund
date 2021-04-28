#include "gtest/gtest.h"
#include "Arduino.h"
#include "Serial.h"

#include "../src/model.h"

using ::testing::Return;

TEST(player, life_delta_plus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToLife(1);
  EXPECT_EQ(41, p->GetLife());	
}

TEST(player, life_delta_minus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToLife(-1);
  EXPECT_EQ(39, p->GetLife());	
}

TEST(player, life_delta_minus_bigger_than_current) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToLife(-41);
  EXPECT_EQ(-1, p->GetLife());	
}

TEST(player, life_default) {
  Edmund::Player* p = new Edmund::Player();
  EXPECT_EQ(40, p->GetLife());	
}

TEST(player, cmdr_dmg_delta_plus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToCommanderDamages(0, 1);
  EXPECT_EQ(1, p->GetCommanderDamages(0));	
}

TEST(player, cmdr_dmg_delta_minus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToCommanderDamages(0, 10);
  p->ApplyDeltaToCommanderDamages(0, -1);
  EXPECT_EQ(9, p->GetCommanderDamages(0));
}

TEST(player, cmdr_dmg_delta_minus_bigger_than_current) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToCommanderDamages(0, -1);
  EXPECT_EQ(0, p->GetCommanderDamages(0));
}

TEST(player, cmdr_dmg_delta_inexsting_player) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToCommanderDamages(PLAYER_COUNT + 1, 10);
  p->ApplyDeltaToCommanderDamages(-1, 10);
  for(int i = 0; i < PLAYER_COUNT; i++)
    EXPECT_EQ(0, p->GetCommanderDamages(i));
}

TEST(player, cmdr_dmg_get_inexsting_player) {
  Edmund::Player* p = new Edmund::Player();
  EXPECT_EQ(0, p->GetCommanderDamages(PLAYER_COUNT + 1));
  EXPECT_EQ(0, p->GetCommanderDamages(-1));
}

TEST(player, cmdr_dmg_default) {
  Edmund::Player* p = new Edmund::Player();
  EXPECT_EQ(0, p->GetCommanderDamages(0));		
}

TEST(player, infect_delta_plus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToInfect(1);
  EXPECT_EQ(1, p->GetInfect());
}

TEST(player, infect_delta_minus_one) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToInfect(10);
  p->ApplyDeltaToInfect(-1);
  EXPECT_EQ(9, p->GetInfect());
}

TEST(player, infect_delta_minus_bigger_than_current) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToInfect(-1);
  EXPECT_EQ(0, p->GetInfect());
}

TEST(player, infect_default) {
  Edmund::Player* p = new Edmund::Player();
  EXPECT_EQ(0, p->GetInfect());
}

TEST(player, reset) {
  Edmund::Player* p = new Edmund::Player();
  p->ApplyDeltaToLife(10);
  p->ApplyDeltaToCommanderDamages(0, 10);
  p->ApplyDeltaToInfect(10);
  p->Reset();
  EXPECT_EQ(0, p->GetInfect());
  EXPECT_EQ(0, p->GetCommanderDamages(0));
  EXPECT_EQ(40, p->GetLife());
}