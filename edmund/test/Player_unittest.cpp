// Copyright 2014 http://switchdevice.com
// This example code is in the public domain.

#include "gtest/gtest.h"
#include "arduino-mock/Arduino.h"
#include "arduino-mock/Serial.h"

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

TEST(player, cmdr_dmg_default) {
  Edmund::Player* p = new Edmund::Player();
  EXPECT_EQ(0, p->GetCommanderDamages(0));		
}