#include "reader.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace reader {
fs::path get_workspace();
bool is_problem(const std::string &filename);

const std::string INPUT_PATH = "input";

Reader::Reader() {
  for (auto entry : fs::directory_iterator(get_workspace() / INPUT_PATH)) {
    fs::path path = entry.path();
    std::string filename = path.filename();

    if (!is_problem(filename)) {
      continue;
    }

    todo.push(path);
  }
}

std::optional<fs::path> Reader::get() {
  if (todo.empty()) {
    return std::nullopt;
  }

  fs::path path = todo.front();
  return path;
}

Reader &Reader::operator++() {
  todo.pop();
  return *this;
}

std::vector<short> Reader::read_problem(const std::string &filepath) {
  std::ifstream file;
  std::vector<short> sheet(std::pow(9, 2), 0);
  char chr;
  int needle = 0;

  file.open(filepath, std::ios::out);

  while (file.get(chr)) {
    if (std::isdigit(chr)) {
      sheet[needle++] = chr - '0';
    }
  }

  file.close();
  return sheet;
}

fs::path get_workspace() {
  std::vector<std::string> references = {".git/", "build/", "main.cpp"};

  for (auto curr = fs::current_path(); curr != fs::path("/");
       curr = curr.parent_path()) {

    for (auto entry : fs::directory_iterator(curr)) {
      auto filename = entry.path().filename();
      auto find = std::find(references.begin(), references.end(), filename);

      if (find != references.end()) {
        return curr;
      }
    }
  }

  return fs::current_path();
}

bool is_problem(const std::string &filename) {
  const static std::string ext = ".txt";

  if (ext.size() > filename.size()) {
    return false;
  }

  int begin = filename.size() - ext.size();
  return filename.compare(begin, ext.size(), ext) == 0;
}

} // namespace reader
