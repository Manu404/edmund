#include "gtest/gtest.h"
#include "arduino-mock/Arduino.h"
#include "arduino-mock/Serial.h"
#include "arduino-mock/SPI.h"

#include "../edmund.ino"

using ::testing::Return;
using namespace Edmund;

namespace {
  std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
  }
  class String : public std::string {
  public:
    String() {}
    String(const String& string) : String(string.c_str()) {}
    String(const std::string& string) : std::string(string) {}
    String(const char* string) : std::string(string) {}

    String substring(int start) {
      return substr(start);
    }
    String substring(int start, int end) {
      return substr(start, end - start);
    }

    String remove(int start) {
      return erase(start);
    }

    void replace(const String& from, const String& to) {
      ReplaceAll(*this, from, to);
    }

    int indexOf(const char needle) {
      return find(needle);
    }
  };
};

TEST(game, get_set_player_life_property) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    g->ApplyDeltaToPlayerProperty(i, Life_property, i + 1);
    EXPECT_EQ(i + 1, g->GetPlayerPropertyValue(i, Life_property));
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

TEST(game, get_set_mana_property) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++) {
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(W_MANA + mana), i + 1);
      EXPECT_EQ(0, g->GetPlayerPropertyValue(i, (PlayerProperties)(W_MANA + mana)));
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
  EXPECT_EQ(5, g->GetManaTypeCount());
}

TEST(game, reset) {
  Edmund::Game* g = new Edmund::Game();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    g->ApplyDeltaToPlayerProperty(i, Infect_property, i + 1);
    g->ApplyDeltaToPlayerProperty(i, Life_property, i + 1);
    for (int target = 0; target < PLAYER_COUNT; target++)
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(target), i + 1);
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++)
      g->ApplyDeltaToPlayerProperty(i, (PlayerProperties)(W_MANA + mana), i + 1);
  }
  g->Reset();
  for (int i = 0; i < PLAYER_COUNT; i++) {
    EXPECT_EQ(40, g->GetPlayerPropertyValue(i, Life_property));
    EXPECT_EQ(0, g->GetPlayerPropertyValue(i, Infect_property));
    for (int target = 0; target < PLAYER_COUNT; target++)
      EXPECT_EQ(0, g->GetPlayerPropertyValue(i, (PlayerProperties)(target)));
    for (int mana = 0; mana < MANA_TYPE_COUNT; mana++)
      EXPECT_EQ(0, g->GetPlayerPropertyValue(i, (PlayerProperties)(W_MANA + mana)));
  }
}