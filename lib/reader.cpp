#include "reader.hpp"
#include <cctype>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace sudoku_reader {
const fs::path INPUT_PATH = fs::current_path() / "input";

bool is_problem(std::string filename);

Reader::Reader(std::string workspace) {
  for (const auto &entry : fs::directory_iterator(INPUT_PATH)) {
    const fs::path path = entry.path();
    const std::string filename = path.filename().string();

    if (!is_problem(filename)) {
      continue;
    }

    todo.push(path);
  }
}

std::optional<fs::path> Reader::front() {
  if (todo.empty()) {
    return std::nullopt;
  }

  fs::path path = todo.front();
  todo.pop();
  return path;
}

std::vector<short> Reader::get_problem(fs::path path) {
  std::ifstream file;
  file.open(path.string(), std::ios::out);

  std::vector<short> sheet(std::pow(9, 2), 0);
  char chr;

  for (int i = 0; file.get(chr); ++i) {
    if (std::isdigit(chr)) {
      sheet[i] = chr - '0';
    }
  }

  file.close();
  return sheet;
}

bool is_problem(std::string filename) {
  const static std::string ending = ".txt";

  if (ending.size() > filename.size()) {
    return false;
  }

  int begin = filename.size() - ending.size();
  return filename.compare(begin, ending.size(), ending);
}

} // namespace sudoku_reader
