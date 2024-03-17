#pragma once

#include <cstdint>
#include <vector>

namespace solver {
class Solver {
public:
  bool solvable;
  std::vector<bool> sheet;
  Solver() : solvable(false){};
  void feed(const std::vector<uint8_t> &problem);
  void solve();
  std::vector<uint8_t> export_();
};
}; // namespace solver
