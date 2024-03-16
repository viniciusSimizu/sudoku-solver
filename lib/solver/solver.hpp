#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace solver {
class Solver {
public:
  bool solvable;
  std::vector<bool> sheet;
  Solver();
  void feed(const std::vector<uint8_t> &problem);
  bool solve(const std::string &name);
};
}; // namespace solver
