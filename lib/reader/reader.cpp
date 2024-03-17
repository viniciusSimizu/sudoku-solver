#include "reader.hpp"
#include "workspace.hpp"
#include <cctype>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace reader {
namespace fs = std::filesystem;

bool is_txt(const std::string &filename);

const static std::string input_dir = "input";

void Reader::read_dir() {
  todo = std::queue<fs::path>();

  for (auto entry :
       fs::directory_iterator(workspace::get_workspace() / input_dir)) {
    fs::path path = entry.path();
    std::string name = path.filename();

    if (!is_txt(name)) {
      continue;
    }

    todo.push(path);
  }
}

std::optional<Sudoku> Reader::get() {
  if (todo.empty()) {
    return std::nullopt;
  }

  fs::path path = todo.front();
  todo.pop();
  return read_problem(path);
}

Sudoku read_problem(const fs::path &filepath) {
  Sudoku sudoku;
  char chr;
  uint8_t needle = 0;
  std::vector<uint8_t> sheet(pow(9, 2), 0);

  std::ifstream file;
  file.open(filepath);

  while (file.get(chr)) {
    if (std::isdigit(chr)) {
      sheet[needle++] = chr - '0';
    }
  }

  file.close();
  sudoku.sheet = sheet;
  sudoku.name = filepath.filename();
  return sudoku;
}

bool is_txt(const std::string &filename) {
  const static std::string ext = ".txt";

  if (ext.size() > filename.size()) {
    return false;
  }

  int begin = filename.size() - ext.size();

  for (int i = 0; i < ext.size(); ++i) {
    if (filename[begin + i] != ext[i]) {
      return false;
    }
  }

  return true;
}

} // namespace reader
