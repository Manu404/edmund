#include "gtest/gtest.h"
#include "Arduino.h"
#include <memory>

#include "../src/hardware/output/pcd8544device.cpp"
#include "outputmocks.h"

using ::testing::Return;
using namespace Edmund;

void testPrintNumberLarge(int number, int length, int expectedResult){
  MockIPCD8544Api* mock = new MockIPCD8544Api();
  EXPECT_CALL(*mock, useMonoBoldFont()).Times(1);
  EXPECT_CALL(*mock, drawChar(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(expectedResult);
  
  Edmund::Hardware::PCD8544OutputDevice* device = new Edmund::Hardware::PCD8544OutputDevice(std::unique_ptr<Edmund::Hardware::IPCD8544Api>(new MockedPCD8544Api(mock)));
  device->PrintNumberLarge(0, 0, number, 0, length);
  delete(device);
}

void testPrintNumberSmall(int number, int length, int expectedResult){
  MockIPCD8544Api* mock = new MockIPCD8544Api();
  EXPECT_CALL(*mock, drawNumericBitmap(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(expectedResult);
  
  Edmund::Hardware::PCD8544OutputDevice* device = new Edmund::Hardware::PCD8544OutputDevice(std::unique_ptr<Edmund::Hardware::IPCD8544Api>(new MockedPCD8544Api(mock)));
  device->PrintNumberSmall(0, 0, number, 0, length);
  delete(device);
}


TEST(hardware_output, givenThreeDigitsValueAndLength3_shouldPrint3Digits) {
  testPrintNumberSmall(123,3,3);
}

TEST(hardware_output, givenTwoDigitsValueAndLength3_shouldPrint2Digits) {
  testPrintNumberSmall(12,3,2);
}

TEST(hardware_output, givenThreeDigitsValueAndLength2_shouldPrint2Digits) {
  testPrintNumberSmall(123,2,2);
}

TEST(hardware_output, givenThreeDigitsValueAndLength3_shouldPrint3Digits_large) {
  testPrintNumberLarge(123,3,3);
}

TEST(hardware_output, givenTwoDigitsValueAndLength3_shouldPrint3Digits_large) {
  testPrintNumberLarge(12,3,3);
}

TEST(hardware_output, givenThreeDigitsValueAndLength2_shouldPrint2Digits_large) {
  testPrintNumberLarge(123,2,2);
}
