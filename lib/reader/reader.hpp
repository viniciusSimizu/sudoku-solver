#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <queue>
#include <string>
#include <vector>

namespace reader {
struct Sudoku {
  std::vector<uint8_t> sheet;
  std::string name;
};

Sudoku read_problem(const std::filesystem::path &filepath);

class Reader {
public:
  std::queue<std::filesystem::path> todo;
  void read_dir();
  std::optional<Sudoku> get();
};
} // namespace reader
