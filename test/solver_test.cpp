#include "iterator.hpp"
#include "solver.hpp"
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

using namespace iterator;

sudoku::sudoku *arrangement_resolved();
sudoku::sudoku *arrangement_partial();
sudoku::sudoku *arrangement_invalid();
bool assert_sheet(sudoku::sudoku &data);
std::vector<uint8_t> *create_sheet(const std::string &txt);
sudoku::sudoku *create_arrangement(const std::string &txt, bool solvable);

int main() {
  std::vector<sudoku::sudoku *> arrangs = {
      arrangement_resolved(), arrangement_partial(), arrangement_invalid()};

  for (sudoku::sudoku *arrang : arrangs) {
    assert(assert_sheet(*arrang));
    sudoku::free(arrang);
  };

  return 0;
};

struct sudoku::sudoku *arrangement_resolved() {
  std::string txt = "1 2 3 7 8 9 4 5 6"
                    "4 5 6 1 2 3 7 8 9"
                    "7 8 9 4 5 6 1 2 3"
                    "3 1 2 9 7 8 6 4 5"
                    "6 4 5 3 1 2 9 7 8"
                    "9 7 8 6 4 5 3 1 2"
                    "2 3 1 8 9 7 5 6 4"
                    "5 6 4 2 3 1 8 9 7"
                    "8 9 7 5 6 4 2 3 1";
  return create_arrangement(txt, true);
}

struct sudoku::sudoku *arrangement_partial() {
  std::string txt = "7 x x x x x 1 x x"
                    "x 9 x x 4 x x x x"
                    "x x x x x x x x 3"
                    "1 x x 2 x x 5 7 x"
                    "x x x x x x x x x"
                    "x x x x x 8 x x x"
                    "x 7 x x x 9 x x x"
                    "x x x 5 x x x x 6"
                    "3 x x x x x x x 8";
  return create_arrangement(txt, true);
}

struct sudoku::sudoku *arrangement_invalid() {
  std::string txt = "x x x x x x 1 1 x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x"
                    "x x x x x x x x x";
  return create_arrangement(txt, false);
}

bool assert_sheet(sudoku::sudoku &data) {
  bool resolvable = data.solved;
  solver::solve(data);

  if (data.solved != resolvable) {
    return false;
  };

  for (uint8_t i = 0; i < std::pow(9, 2); ++i) {
    if ((*data.sheet)[i] == 0) {
      if (data.solved == true) {
        return false;
      };

      continue;
    };

    RowIt rowIt = i;
    ColumnIt columnIt = i;
    BlockIt blockIt = i;
    std::vector<It *> its = {&rowIt, &columnIt, &blockIt};

    for (const auto &it : its) {
      int8_t j;

      while ((j = it->next()) != -1) {
        if (i == j)
          continue;

        if ((*data.sheet)[i] == (*data.sheet)[j]) {
          return false;
        };
      };
    };
  };

  return true;
};

std::vector<uint8_t> *create_sheet(const std::string &txt) {
  std::vector<uint8_t> *sheet = new std::vector<uint8_t>(std::pow(9, 2));
  uint8_t i = 0;

  for (char chr : txt) {
    if (std::isdigit(chr)) {
      (*sheet)[i] = chr - '0';
    } else if (chr == 'x') {
      (*sheet)[i] = 0;
    } else {
      continue;
    };

    ++i;
  };

  return sheet;
};

struct sudoku::sudoku *create_arrangement(const std::string &txt,
                                          bool solvable) {
  sudoku::sudoku *data = new sudoku::sudoku;
  data->sheet = create_sheet(txt);
  data->solved = solvable;
  return data;
};
