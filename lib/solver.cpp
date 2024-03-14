#include "solver.hpp"
#include <cmath>
#include <iostream>
#include <vector>

namespace solver {
int get_idx(int x, int y);
int get_x(int idx);
int get_y(int idx);
int get_begin(int idx);

std::vector<int> insert_value(int idx, short value, std::vector<bool> &sheet);
bool can_insert(int idx, short value, const std::vector<bool> &sheet);
void undo_value(const std::vector<int> &exclude, std::vector<bool> &sheet);
void solve_problem(int idx, std::vector<bool> &sheet, bool &solved);

Solver::Solver() : sheet(std::vector<bool>(std::pow(9, 3))), solvable(false) {}

void Solver::feed(const std::vector<short> &problem) {
  for (int i = 0; i < sheet.size(); ++i) {
    sheet[i] = true;
  }

  for (int i = 0; i < problem.size(); ++i) {
    int idx = i * 9;
    short value = problem[i];

    if (value == 0) {
      continue;
    }

    if (!can_insert(idx, value, sheet)) {
      solvable = false;
      return;
    }

    insert_value(idx, value, sheet);
  }

  solvable = true;
}

bool Solver::solve(const std::string &name) {
  if (!solvable) {
    std::cout << name << " aborted\n";
    return false;
  }

  bool solved = false;
  solve_problem(0, sheet, solved);

  if (!solved) {
    solvable = false;
    return false;
  }

  return true;
}

BlockIt::BlockIt(int idx) : It() {
  x = int(get_x(idx) / 3) * 3;
  y = int(get_y(idx) / 3) * 3;
}

int BlockIt::next() {
  if (needle >= 9) {
    return -1;
  }

  short column = needle % 3;
  short row = needle / 3;
  ++needle;

  return get_idx(x + column, y + row);
}

RowIt::RowIt(int idx) {
  x = 0;
  y = get_y(idx);
}

int RowIt::next() {
  if (needle >= 9) {
    return -1;
  }
  return get_idx(needle++, y);
}

ColumnIt::ColumnIt(int idx) {
  x = get_x(idx);
  y = 0;
}

int ColumnIt::next() {
  if (needle >= 9) {
    return -1;
  }
  return get_idx(x, needle++);
}

int get_x(int idx) { return int(idx / 9) % 9; }
int get_y(int idx) { return int(idx / std::pow(9, 2)); }
int get_idx(int x, int y) { return y * std::pow(9, 2) + x * 9; }
int get_begin(int idx) { return idx - idx % 9; }

bool can_insert(int idx, short value, const std::vector<bool> &sheet) {
  int needle = get_begin(idx);

  if (!sheet[needle + value - 1]) {
    return false;
  }

  BlockIt blockIt = needle;
  RowIt rowIt = needle;
  ColumnIt columnIt = needle;
  std::vector<It *> iterators = {&blockIt, &rowIt, &columnIt};

  for (const auto &it : iterators) {
    for (int target = it->next(); target != -1; target = it->next()) {
      bool other_possible = false;

      if (target == needle) {
        continue;
      }

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
  BlockIt blockIt = idx;
  RowIt rowIt = idx;
  ColumnIt columnIt = idx;
  std::vector<It *> iterators = {&blockIt, &rowIt, &columnIt};

  for (const auto &it : iterators) {
    for (int target = it->next(); target != -1; target = it->next()) {
      if (target == get_begin(idx)) {
        continue;
      }

      target += value - 1;
      if (sheet[target]) {
        revert.push_back(target);
      }
      sheet[target] = false;
    }
  }

  return revert;
}

void undo_value(const std::vector<int> &exclude, std::vector<bool> &sheet) {
  for (int target : exclude) {
    sheet[target] = true;
  }
}

void solve_problem(int idx, std::vector<bool> &sheet, bool &solved) {
  idx = get_begin(idx);

  if (idx >= sheet.size()) {
    solved = true;
    return;
  }

  for (int i = 0; i < 9; ++i) {
    if (!sheet[idx + i]) {
      continue;
    }

    auto revert = insert_value(idx, i, sheet);
    solve_problem(idx + 9, sheet, solved);

    if (solved) {
      return;
    }

    undo_value(revert, sheet);
  }
}
}; // namespace solver
