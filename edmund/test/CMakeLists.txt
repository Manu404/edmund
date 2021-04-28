cmake_minimum_required(VERSION 2.8.8)
project(test-all)

find_package(Threads REQUIRED)
add_subdirectory(arduino_mock)

include_directories(
    ${ARDUINO_MOCK_INCLUDE_DIRS}
    ${ARDUINO_MOCK_LIBS_DIR}/lib/gtest/gtest/src/gtest/include
    ${ARDUINO_MOCK_LIBS_DIR}/lib/gmock/gmock/src/gmock/include
)

file(GLOB LIB_SRCS "../src/*.h")
file(GLOB LIB_SRCS "../src/*.cpp")
file(GLOB SRCS "*.cpp")

add_executable(test-all ${SRCS} ${LIB_SRCS})

target_link_libraries(test-all
    ${ARDUINO_MOCK_LIBS_DIR}/lib/gtest/gtest/src/gtest-build/libgtest.a
    ${ARDUINO_MOCK_LIBS_DIR}/lib/gmock/gmock/src/gmock-build/libgmock.a
    ${ARDUINO_MOCK_LIBS_DIR}/dist/lib/libarduino_mock.a
    ${CMAKE_THREAD_LIBS_INIT}
)

add_definitions( -DARDUINO=180 )

add_dependencies(test-all arduino_mock)

enable_testing()
add_test(TestAll test-all)
