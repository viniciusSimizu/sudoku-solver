#include "iterator.hpp"
#include "solver.hpp"
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

using namespace iterator;

struct arrangement {
  sudoku::sudoku *sudoku;
  bool solvable;
};

arrangement *arrangement_resolved();
arrangement *arrangement_partial();
arrangement *arrangement_invalid();
bool assert_sheet(arrangement &data);
std::vector<uint8_t> *create_sheet(const std::string &txt);
arrangement *create_arrangement(const std::string &txt, bool solvable);

int main() {
  std::vector<arrangement *> cases = {
      arrangement_resolved(), arrangement_partial(), arrangement_invalid()};

  for (arrangement *case_ : cases) {
    bool result = assert_sheet(*case_);
    sudoku::free(case_->sudoku);
    delete case_;

    assert(result);
  };

  return 0;
};

arrangement *arrangement_resolved() {
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

arrangement *arrangement_partial() {
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

arrangement *arrangement_invalid() {
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

bool assert_sheet(arrangement &data) {
  sudoku::sudoku *case_ = data.sudoku;
  std::vector<uint8_t> case_cpy(*case_->sheet);

  solver::solve(*case_);

  if (case_->solved != data.solvable) {
    return false;
  };

  if (!data.solvable) {
    for (uint8_t i = 0; i < std::pow(9, 2); ++i) {
      if ((*case_->sheet)[i] != case_cpy[i]) {
        return false;
      };
    };

    return true;
  };

  for (uint8_t i = 0; i < std::pow(9, 2); ++i) {
    if ((*case_->sheet)[i] == 0) {
      return false;
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

        if ((*case_->sheet)[i] == (*case_->sheet)[j]) {
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

arrangement *create_arrangement(const std::string &txt, bool solvable) {
  arrangement *data = new arrangement;
  sudoku::sudoku *case_ = new sudoku::sudoku;

  case_->sheet = create_sheet(txt);
  case_->solved = false;
	case_->filename = nullptr;
  data->sudoku = case_;
  data->solvable = solvable;

  return data;
};
