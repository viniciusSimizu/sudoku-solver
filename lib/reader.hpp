#pragma once

#include <filesystem>
#include <optional>
#include <queue>
#include <string>
#include <vector>

namespace reader {
std::filesystem::path get_workspace();

class Reader {
public:
  Reader();
  std::optional<std::filesystem::path> get();
  std::vector<short> read_problem(const std::string &filepath);
  Reader &operator++();

private:
  std::queue<std::filesystem::path> todo;
};
} // namespace reader
