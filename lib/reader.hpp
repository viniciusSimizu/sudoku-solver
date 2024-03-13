#pragma once

#include <filesystem>
#include <optional>
#include <queue>
#include <string>
#include <vector>

namespace sudoku_reader {

class Reader {
public:
  Reader(std::string workspace);
  std::optional<std::filesystem::path> front();
  std::vector<short> get_problem(std::filesystem::path path);

private:
  std::queue<std::filesystem::path> todo;
};
} // namespace sudoku_reader
