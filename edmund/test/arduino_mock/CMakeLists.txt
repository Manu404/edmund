cmake_minimum_required(VERSION 2.8.8)
project(arduino_mock_builder C CXX)
include(ExternalProject)

ExternalProject_Add(arduino_mock
    GIT_REPOSITORY https://github.com/Manu404/arduino-mock.git
    GIT_TAG master
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/arduino_mock
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(arduino_mock source_dir)
set(ARDUINO_MOCK_INCLUDE_DIRS ${source_dir}/include/arduino-mock PARENT_SCOPE)

ExternalProject_Get_Property(arduino_mock binary_dir)
set(ARDUINO_MOCK_LIBS_DIR ${binary_dir} PARENT_SCOPE)
