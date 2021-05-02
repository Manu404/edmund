cmake_minimum_required(VERSION 3.14)
project(test-all)


project (ValgrindExample)

find_package(Threads REQUIRED)

# If we are a stand alone project not included with add_subdirectory() and
# googletest, e.g. googlemock is not provided make sure to download it.
include(FetchContent)

FetchContent_Declare(googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.10.0)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(arduino-mock
        GIT_REPOSITORY https://github.com/Manu404/arduino-mock.git)

FetchContent_MakeAvailable(arduino-mock)    

include_directories(
    ./build/_deps/arduino-mock-src/include/arduino-mock
    ./build/_deps/arduino-mock-src/include
    ./build/_deps/googletest-src/googlemock/include
    ./build/_deps/googletest-src/googletest/include
)

file(GLOB LIB_SRCS "../src/*.h")
file(GLOB LIB_SRCS "../src/*.cpp")
file(GLOB SRCS "*.cpp")

add_executable(test-all ${SRCS} ${LIB_SRCS})

target_link_libraries(test-all
    gtest gmock gtest_main
    arduino_mock
    ${CMAKE_THREAD_LIBS_INIT}
)

include (CTest)
add_dependencies(test-all arduino_mock gtest gmock gtest_main)

add_definitions( -DARDUINO=180 )
target_compile_features(test-all PUBLIC cxx_std_11)
set_target_properties(test-all PROPERTIES CXX_EXTENSIONS OFF)

add_test(TestAll test-all)