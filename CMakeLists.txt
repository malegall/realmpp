# --- Project Setup ---
cmake_minimum_required(VERSION 3.16)
project(RealmPP VERSION 1.0 LANGUAGES CXX)

# --- Set C++ Standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Main Executable ---
add_executable(RealmPP src/main.cpp)
target_include_directories(RealmPP PRIVATE include)

# --- Testing Setup ---
enable_testing()

# Find the Google Test package. If not found, it will be fetched.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

# --- Test Executable ---
add_executable(
  run_tests
  tests/core/bounding_box_test.cpp
  tests/core/grid_test.cpp
  tests/core/point_test.cpp
  tests/core/traits_test.cpp
)

set_target_properties(run_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)

target_include_directories(run_tests PRIVATE include)
target_link_libraries(
  run_tests
  PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
