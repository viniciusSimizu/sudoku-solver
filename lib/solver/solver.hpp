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

struct It {
public:
  virtual int next() = 0;

protected:
  int needle, x, y;
  It() : needle(0), x(-1), y(-1){};
};

struct BlockIt : It {
public:
  BlockIt(int idx_2d);
  int next();
};

struct RowIt : It {
public:
  RowIt(int idx_2d);
  int next();
};

struct ColumnIt : It {
public:
  ColumnIt(int idx_2d);
  int next();
};
}; // namespace solver
