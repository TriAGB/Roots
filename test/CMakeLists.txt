# enable_testing()

add_executable(
  lib_test 
  test_command_line_parser.cpp
  test_tangent.cpp
  test_chord.cpp
)
target_link_libraries(
  lib_test
  lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_test)
