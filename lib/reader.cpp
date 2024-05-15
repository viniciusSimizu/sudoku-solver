#include "reader.hpp"
#include "logger.hpp"
#include "sudoku.hpp"
#include "workspace.hpp"
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace reader {
namespace fs = std::filesystem;

std::optional<fs::path> cwd = find_workspace();

std::optional<sudoku::sudoku *> scan_file(const std::string &filename);
fs::path find_file(const std::string &filename);

std::vector<sudoku::sudoku *> search_problems() {
  logger::info("searching files");

  if (!cwd.has_value()) {
    logger::error("workspace not found");
    std::exit(201);
  };

  std::vector<sudoku::sudoku *> files;

  for (auto entry : fs::directory_iterator(cwd.value() / INPUT)) {
    std::optional<sudoku::sudoku *> data = scan_file(entry.path().filename());

    if (data.has_value()) {
      logger::info("file scanned " + *data.value()->filename);
      files.push_back(data.value());
    }
  };

  logger::info("searching files [finished]");
  return files;
};

std::optional<sudoku::sudoku *> scan_file(const std::string &filename) {
  fs::path filepath = find_file(filename);
  auto *sheet = new std::vector<uint8_t>(std::pow(9, 2));

  std::ifstream file;
  file.open(filepath);

  char chr;
  std::size_t i = 0;

  while (file.get(chr)) {
    if (i > std::pow(9, 2)) {
      break;
    }

    if (std::isdigit(chr)) {
      (*sheet)[i++] = chr - '0';
    };
  };

  file.close();

  if (i > std::pow(9, 2)) {
    delete sheet;
    return std::nullopt;
  };

  auto *data = new sudoku::sudoku;
  data->sheet = sheet;
  data->filename = &filename;
  data->solved = false;

  return data;
};

fs::path find_file(const std::string &filename) {
  return cwd.value() / INPUT / filename;
};

} // namespace reader
