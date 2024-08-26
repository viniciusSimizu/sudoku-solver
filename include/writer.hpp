#pragma once

#include "sudoku.hpp"

namespace writer {

#define OUTPUT "output"
#define ENDING "_solved.txt"

void save(sudoku::sudoku &data);

}; // namespace writer
