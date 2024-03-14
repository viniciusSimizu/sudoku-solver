#pragma once

#include <string>
#include <vector>

namespace solver {
int get_offset_x(int idx, int x);
int get_offset_y(int idx, int y);
int get_offset_xy(int idx, int x, int y);

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
  std::vector<bool> sheet;
  Solver();
  void feed(std::vector<short> problem);
  bool solve(std::string name);

private:
  bool solvable;
};
}; // namespace solver
