#pragma once

#include <vector>

namespace solver {
struct It {
public:
  virtual int next() = 0;

protected:
  int begin, curr;
  It() : curr(0), begin(-1){};
};

struct BlockIt : public It {
public:
  BlockIt(int idx);
  int next();
};

struct LineIt : public It {
public:
  LineIt(int idx);
  int next();
};

struct ColumnIt : public It {
public:
  ColumnIt(int idx);
  int next();
};

class Solver {
public:
  Solver();
  void feed(std::vector<short> problem);
  void solve();

private:
  std::vector<bool> sheet;
  bool solvable;
};
}; // namespace solver
