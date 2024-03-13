#include "solver.hpp"
#include <cmath>
#include <vector>

namespace solver {

int get_offset_x(int idx, int x);
int get_offset_y(int idx, int y);
int get_offset_xy(int idx, int x, int y);
bool can_insert(int idx, short value, std::vector<bool> &sheet);
std::vector<int> insert_value(int idx, short value, std::vector<bool> &sheet);
void remove_value(std::vector<int> exclude, std::vector<bool> &sheet);

BlockIt::BlockIt(int idx) : It() {
  int x = int(idx / 3 * 9) % 3;
  int y = int(idx / std::pow(9, 2) * 3) % 3;
  int z = idx % 9;

  begin = get_offset_xy(z, x, y);
}

int BlockIt::next() {
  if (curr >= 9) {
    return -1;
  }

  short w = curr % 3;
  short h = curr / 3;
  ++curr;

  return get_offset_xy(begin, w, h);
}

LineIt::LineIt(int idx) : It() {
  int y = idx / std::pow(9, 2);
  int z = idx % 9;

  int begin = get_offset_y(z, y);
}

int LineIt::next() {
  if (curr >= 9) {
    return -1;
  }
  return get_offset_x(begin, curr++);
}

ColumnIt::ColumnIt(int idx) : It() {
  int x = int(idx / 9) % 9;
  int z = idx % 9;

  int begin = get_offset_x(z, x);
}

int ColumnIt::next() {
  if (curr >= 9) {
    return -1;
  }
  return get_offset_y(begin, curr++);
}

Solver::Solver() : sheet(std::vector<bool>(std::pow(9, 3))), solvable(true) {}

void Solver::feed(std::vector<short> problem) {
  for (int i = 0; i < sheet.size(); ++i) {
    sheet[i] = true;
  }

  for (int i = 0; i < problem.size(); ++i) {
    short value = problem[i];

    if (value == 0) {
      continue;
    }

    if (!can_insert(i * 9, value, sheet)) {
      solvable = false;
      return;
    }
  }

  solvable = true;
}

int get_start(int idx) { return std::floor(idx / 9) * 9; }
int get_offset_x(int idx, int x) { return idx + x * 9; }
int get_offset_y(int idx, int y) { return idx + y * std::pow(9, 2); }
int get_offset_xy(int idx, int x, int y) {
  return get_offset_y(get_offset_x(idx, x), y);
}

bool can_insert(int idx, short value, std::vector<bool> &sheet) {
  int curr = idx - idx % 9;

  if (!sheet[curr + value - 1]) {
    return false;
  }

  BlockIt blockIt = curr;
  LineIt lineIt = curr;
  ColumnIt columnIt = curr;
  std::vector<It *> iterators = {&blockIt, &lineIt, &columnIt};

  for (const auto &it : iterators) {
    for (int target = it->next(); target != -1; target = it->next()) {
      bool other_possible = false;

      for (int i = 0; i < 9; ++i) {
        if (i != value - 1 && sheet[target + i]) {
          other_possible = true;
          break;
        }
      }

      if (!other_possible) {
        return false;
      }
    }
  }

  return true;
}

std::vector<int> insert_value(int idx, short value, std::vector<bool> &sheet) {
  std::vector<int> revert(8 * 3 - 4);
  int curr = idx - idx % 9 + value - 1;
  BlockIt blockIt = curr;
  LineIt lineIt = curr;
  ColumnIt columnIt = curr;
  std::vector<It *> iterators = {&blockIt, &lineIt, &columnIt};

  for (const auto &it : iterators) {
    for (int target = it->next(); target != -1; target = it->next()) {
      if (target == curr) {
        continue;
      }

      if (sheet[target]) {
        revert.push_back(target);
      }

      sheet[target] = false;
    }
  }

  return revert;
}

void remove_value(std::vector<int> exclude, std::vector<bool> &sheet) {
  for (int target : exclude) {
    sheet[target] = true;
  }
}
}; // namespace solver
