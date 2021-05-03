#include "gtest/gtest.h"
#include "Arduino.h"
#include "Serial.h"

#include "model.h"

using ::testing::Return;
using namespace Edmund;

TEST(manapool, apply_positive_delta) {
  Edmund::ManaPoolState* p = new Edmund::ManaPoolState();
  p->ApplyDeltaToManaPoolContent(W_MANA, 1);
  EXPECT_EQ(1, p->GetManaPoolContent(W_MANA));
  delete(p);
}

TEST(manapool, apply_negative_delta) {
  Edmund::ManaPoolState* p = new Edmund::ManaPoolState();
  p->ApplyDeltaToManaPoolContent(W_MANA, 10);
  p->ApplyDeltaToManaPoolContent(W_MANA, -1);
  EXPECT_EQ(9, p->GetManaPoolContent(W_MANA));
  delete(p);
}

TEST(manapool, apply_negative_delta_bigger_than_current) {
  Edmund::ManaPoolState* p = new Edmund::ManaPoolState();
  p->ApplyDeltaToManaPoolContent(W_MANA, -1);
  EXPECT_EQ(0, p->GetManaPoolContent(W_MANA));
  delete(p);
}

TEST(manapool, apply_match_get) {
  Edmund::ManaPoolState* p = new Edmund::ManaPoolState();
  p->ApplyDeltaToManaPoolContent(W_MANA, 1);
  p->ApplyDeltaToManaPoolContent(U_MANA, 2);
  p->ApplyDeltaToManaPoolContent(B_MANA, 3);
  p->ApplyDeltaToManaPoolContent(R_MANA, 4);
  p->ApplyDeltaToManaPoolContent(G_MANA, 5);
  p->ApplyDeltaToManaPoolContent(X_MANA, 6);
  EXPECT_EQ(1, p->GetManaPoolContent(W_MANA));
  EXPECT_EQ(2, p->GetManaPoolContent(U_MANA));
  EXPECT_EQ(3, p->GetManaPoolContent(B_MANA));
  EXPECT_EQ(4, p->GetManaPoolContent(R_MANA));
  EXPECT_EQ(5, p->GetManaPoolContent(G_MANA));
  EXPECT_EQ(6, p->GetManaPoolContent(X_MANA));
  delete(p);
}


TEST(manapool, empty) {
  Edmund::ManaPoolState* p = new Edmund::ManaPoolState();
  p->ApplyDeltaToManaPoolContent(W_MANA, 1);
  p->ApplyDeltaToManaPoolContent(U_MANA, 2);
  p->ApplyDeltaToManaPoolContent(B_MANA, 3);
  p->ApplyDeltaToManaPoolContent(R_MANA, 4);
  p->ApplyDeltaToManaPoolContent(G_MANA, 5);
  p->ApplyDeltaToManaPoolContent(X_MANA, 6);
  p->Empty();
  EXPECT_EQ(0, p->GetManaPoolContent(W_MANA));
  EXPECT_EQ(0, p->GetManaPoolContent(U_MANA));
  EXPECT_EQ(0, p->GetManaPoolContent(B_MANA));
  EXPECT_EQ(0, p->GetManaPoolContent(R_MANA));
  EXPECT_EQ(0, p->GetManaPoolContent(G_MANA));
  EXPECT_EQ(0, p->GetManaPoolContent(X_MANA));
  delete(p);
}