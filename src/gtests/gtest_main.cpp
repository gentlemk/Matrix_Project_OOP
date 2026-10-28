#include <iostream>

#include "gtest_test_classes.hpp"

int main(int argc, char **argv) {
  std::cout << "Запуск тестов GTest..." << std::endl;
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
