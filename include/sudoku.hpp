#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace sudoku {

struct sudoku {
  std::vector<uint8_t> *sheet;
  const std::string *filename;
  bool solved;
};

void free(sudoku *data);

}; // namespace sudoku
