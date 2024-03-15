#include "solver.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace solver {
std::vector<int> insert_value(int idx, uint8_t value, std::vector<bool> &sheet);
bool is_valid_problem(const std::vector<uint8_t> &problem);
void undo_value(const std::vector<int> &exclude, std::vector<bool> &sheet);
void solve_problem(int idx, std::vector<bool> &sheet, bool &solved);

int get_2d_to_3d_idx(int idx);

Solver::Solver() : sheet(std::vector<bool>(pow(9, 3))), solvable(false) {}

void Solver::feed(const std::vector<uint8_t> &problem) {
  if (!is_valid_problem(problem)) {
    solvable = false;
    return;
  }

  for (int i = 0; i < sheet.size(); ++i) {
    sheet[i] = true;
  }

  for (int i = 0; i < problem.size(); ++i) {
    uint8_t value = problem[i];

    if (value == 0) {
      continue;
    }

    insert_value(i, value, sheet);
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

BlockIt::BlockIt(int idx_2d) : It() {
  x = int((idx_2d % 9) / 3) * 3;
  y = int((idx_2d / 9) / 3) * 3;
}

int BlockIt::next() {
  if (needle >= 9) {
    return -1;
  }

  uint8_t column = needle % 3;
  uint8_t row = needle / 3;
  ++needle;

  return x + column + (y + row) * 9;
}

RowIt::RowIt(int idx_2d) {
  x = 0;
  y = idx_2d / 9;
}

int RowIt::next() {
  if (needle >= 9) {
    return -1;
  }
  return needle++ + y * 9;
}

ColumnIt::ColumnIt(int idx_2d) {
  x = idx_2d % 9;
  y = 0;
}

int ColumnIt::next() {
  if (needle >= 9) {
    return -1;
  }
  return x + needle++ * 9;
}

bool is_valid_problem(const std::vector<uint8_t> &problem) {
  for (int idx_2d = 0; idx_2d < problem.size(); ++idx_2d) {
    uint8_t value = problem[idx_2d];

    if (value == 0) {
      continue;
    }

    BlockIt blockIt = idx_2d;
    RowIt rowIt = idx_2d;
    ColumnIt columnIt = idx_2d;
    std::vector<It *> iterators{&blockIt, &rowIt, &columnIt};

    for (const auto &it : iterators) {
      for (int curr = it->next(); curr != -1; curr = it->next()) {
        if (curr != idx_2d && problem[curr] == value) {
          return false;
        }
      }
    }
  }

  return true;
}

std::vector<int> insert_value(int idx_2d, uint8_t value,
                              std::vector<bool> &sheet) {

  int idx_3d = get_2d_to_3d_idx(idx_2d);
  std::vector<int> revert(8 * 3 - 4 + 8);
  BlockIt blockIt = idx_2d;
  RowIt rowIt = idx_2d;
  ColumnIt columnIt = idx_2d;
  std::vector<It *> iterators = {&blockIt, &rowIt, &columnIt};

  for (int i = 0; i < 9; ++i) {
    if (i != value - 1 && sheet[idx_3d + i]) {
      revert.push_back(idx_3d + i);
      sheet[idx_3d + i] = false;
    }
  }

  for (const auto &it : iterators) {
    for (int curr = it->next(); curr != -1; curr = it->next()) {
      if (curr == idx_2d) {
        continue;
      }

      idx_3d = get_2d_to_3d_idx(curr) + value - 1;
      if (sheet[idx_3d]) {
        revert.push_back(idx_3d);
        sheet[idx_3d] = false;
      }
    }
  }

  return revert;
}

void undo_value(const std::vector<int> &exclude, std::vector<bool> &sheet) {
  for (int target : exclude) {
    sheet[target] = true;
  }
}

void solve_problem(int idx_2d, std::vector<bool> &sheet, bool &solved) {
  int idx_3d = get_2d_to_3d_idx(idx_2d);

  if (idx_3d >= sheet.size()) {
    solved = true;
    return;
  }

  for (int i = 0; i < 9; ++i) {
    if (!sheet[idx_3d + i]) {
      continue;
    }

    auto revert = insert_value(idx_2d, i, sheet);
    solve_problem(idx_2d + 1, sheet, solved);

    if (solved) {
      return;
    }

    undo_value(revert, sheet);
  }
}

int get_2d_to_3d_idx(int idx) {
  uint8_t x = idx % 9;
  uint8_t y = idx / 9;
  return x * 9 + y * pow(9, 2);
}
}; // namespace solver
