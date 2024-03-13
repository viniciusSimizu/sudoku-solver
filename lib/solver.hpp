#pragma once

#include <vector>

namespace solver {
class Solver {
public:
  Solver();
  void feed(std::vector<short> problem);
  void solve();

private:
  std::vector<bool> sheet;
};
}; // namespace solver
