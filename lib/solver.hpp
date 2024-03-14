#pragma once

#include <string>
#include <vector>

namespace solver {
class Solver {
public:
  std::vector<bool> sheet;
  Solver();
  void feed(const std::vector<short> &problem);
  bool solve(const std::string &name);

private:
  bool solvable;
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
  BlockIt(int idx);
  int next();
};

struct RowIt : It {
public:
  RowIt(int idx);
  int next();
};

struct ColumnIt : It {
public:
  ColumnIt(int idx);
  int next();
};
}; // namespace solver
