#pragma once

#include "sudoku.hpp"
#include <optional>
#include <string>
#include <vector>

namespace reader {

#define INPUT "input"

std::vector<std::string> search_problems();
std::optional<sudoku::sudoku*> read_sheet(std::string &filename);

} // namespace reader
