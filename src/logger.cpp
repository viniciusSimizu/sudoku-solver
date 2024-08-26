#include "logger.hpp"
#include <iostream>

namespace logger {

void info(const std::string &msg) {
  std::cout << "Info: " << msg << std::endl;
};

void error(const std::string &msg) {
  std::cout << "Error: " << msg << std::endl;
};

}; // namespace logger
