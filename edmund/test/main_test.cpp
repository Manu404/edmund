#include "gtest/gtest.h"
#include "Arduino.h"

#include "game.h"

using ::testing::Return;
using namespace Edmund;

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ardu, test_mock) {
  ArduinoMock* arduinoMock = arduinoMockInstance();
  EXPECT_CALL(*arduinoMock, digitalRead(2)).WillOnce(Return(1));
  digitalRead(2);
  releaseArduinoMock();
}