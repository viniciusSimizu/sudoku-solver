#pragma once

#include "sudoku.hpp"
#include <vector>

namespace reader {

#define INPUT "input"
#define EXT ".txt"

std::vector<sudoku::sudoku *> search_problems();

} // namespace reader
