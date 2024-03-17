#include "solver.hpp"
#include "iterator.hpp"
#include <cmath>
#include <cstdint>
#include <vector>

using namespace iterator;

namespace solver {
std::vector<uint16_t> insert_value(uint8_t idx_2d, uint8_t z,
                                   std::vector<bool> &sheet);
bool is_valid_problem(const std::vector<uint8_t> &problem);
void solve_problem(uint8_t idx_2d, std::vector<bool> &sheet, bool &solved);

uint16_t get_2d_to_3d_idx(uint8_t idx_2d);

void Solver::feed(const std::vector<uint8_t> &problem) {
  if (!is_valid_problem(problem)) {
    solvable = false;
    return;
  }

  sheet = std::vector<bool>(pow(9, 3), true);

  for (uint8_t idx_2d = 0; idx_2d < pow(9, 2); ++idx_2d) {
    uint8_t z = problem[idx_2d];

    if (z == 0) {
      continue;
    }

    insert_value(idx_2d, z, sheet);
  }

  solvable = true;
}

void Solver::solve() {
  if (!solvable) {
    return;
  }

  bool solved = false;
  solve_problem(0, sheet, solved);

  if (!solved) {
    solvable = false;
  }
}

std::vector<uint8_t> Solver::export_() {
  std::vector<uint8_t> matrix(pow(9, 2), 0);

  if (!solvable) {
    return matrix;
  }

  for (int idx_2d = 0; idx_2d < pow(9, 2); ++idx_2d) {
    uint16_t idx_3d = get_2d_to_3d_idx(idx_2d);

    for (int z = 0; z < 9; ++z) {
      if (sheet[idx_3d + z]) {
        matrix[idx_2d] = z + 1;
        break;
      }
    }
  }

  return matrix;
}

std::vector<uint16_t> insert_value(uint8_t idx_2d, uint8_t z,
                                   std::vector<bool> &sheet) {

  uint16_t idx_3d = get_2d_to_3d_idx(idx_2d);
  std::vector<uint16_t> revert(8 * 3 - 4 + 8);
  BlockIt blockIt = idx_2d;
  RowIt rowIt = idx_2d;
  ColumnIt columnIt = idx_2d;
  std::vector<It *> iterators = {&blockIt, &rowIt, &columnIt};

  for (int i = 0; i < 9; ++i) {
    if (i + 1 == z) {
      continue;
    }

    if (sheet[idx_3d + i]) {
      revert.push_back(idx_3d + i);
      sheet[idx_3d + i] = false;
    }
  }

  for (const auto &it : iterators) {
    for (int curr = it->next(); curr != -1; curr = it->next()) {
      if (curr == idx_2d) {
        continue;
      }

      idx_3d = get_2d_to_3d_idx(curr) + z - 1;
      if (sheet[idx_3d]) {
        revert.push_back(idx_3d);
        sheet[idx_3d] = false;
      }
    }
  }

  return revert;
}

bool is_valid_problem(const std::vector<uint8_t> &problem) {
  for (uint8_t idx_2d = 0; idx_2d < problem.size(); ++idx_2d) {
    uint8_t z = problem[idx_2d];

    if (z == 0) {
      continue;
    }

    BlockIt blockIt = idx_2d;
    RowIt rowIt = idx_2d;
    ColumnIt columnIt = idx_2d;
    std::vector<It *> iterators{&blockIt, &rowIt, &columnIt};

    for (const auto &it : iterators) {
      for (int curr = it->next(); curr != -1; curr = it->next()) {
        if (curr != idx_2d && problem[curr] == z) {
          return false;
        }
      }
    }
  }

  return true;
}

void solve_problem(uint8_t idx_2d, std::vector<bool> &sheet, bool &solved) {
  if (idx_2d >= pow(9, 2)) {
    solved = true;
    return;
  }
  uint16_t idx_3d = get_2d_to_3d_idx(idx_2d);

  for (int z = 0; z < 9; ++z) {
    if (!sheet[idx_3d + z]) {
      continue;
    }

    auto revert = insert_value(idx_2d, z + 1, sheet);
    solve_problem(idx_2d + 1, sheet, solved);

    if (solved) {
      return;
    }

    for (uint16_t idx_3d : revert) {
      sheet[idx_3d] = true;
    }
  }
}

uint16_t get_2d_to_3d_idx(uint8_t idx_2d) {
  uint8_t x = idx_2d % 9;
  uint8_t y = idx_2d / 9;
  return x * 9 + y * pow(9, 2);
}
}; // namespace solver
