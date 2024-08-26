#include "solver.hpp"
#include "iterator.hpp"
#include "logger.hpp"
#include <cmath>
#include <vector>

namespace solver {

using namespace iterator;

bool try_solve(uint8_t idx, std::vector<uint8_t> &sheet);
bool possible_value(uint8_t value, uint8_t idx,
                    const std::vector<uint8_t> &arr);
bool is_valid(std::vector<uint8_t> &sheet);

void solve(sudoku::sudoku &data) {
  logger::info("solving " + *data.filename);

  if (!is_valid(*data.sheet)) {
    data.solved = false;
    logger::info("unsolvable case");
    return;
  };

  data.solved = try_solve(0, *data.sheet);
  logger::info("solving [executed]");
};

bool try_solve(uint8_t idx, std::vector<uint8_t> &sheet) {
  if (idx >= std::pow(9, 2)) {
    return true;
  };

  if (sheet[idx] != 0) {
    return try_solve(idx + 1, sheet);
  };

  for (uint8_t i = 1; i <= 9; ++i) {
    if (!possible_value(i, idx, sheet)) {
      continue;
    };

    sheet[idx] = i;

    if (try_solve(idx + 1, sheet)) {
      return true;
    };
  };

  sheet[idx] = 0;
  return false;
};

bool possible_value(uint8_t value, uint8_t idx,
                    const std::vector<uint8_t> &arr) {
  RowIt rowIt = idx;
  ColumnIt columnIt = idx;
  BlockIt blockIt = idx;
  std::vector<It *> its{&rowIt, &columnIt, &blockIt};

  for (const auto &it : its) {
    int8_t it_idx;

    while ((it_idx = it->next()) != -1) {
      if (it_idx == idx) {
        continue;
      };

      if (arr[it_idx] == value) {
        return false;
      };
    };
  };

  return true;
};

bool is_valid(std::vector<uint8_t> &sheet) {
  for (uint8_t i = 0; i < std::pow(9, 2); ++i) {
    if (sheet[i] == 0) {
      continue;
    };

    if (!possible_value(sheet[i], i, sheet)) {
      return false;
    };
  };

  return true;
};

}; // namespace solver
