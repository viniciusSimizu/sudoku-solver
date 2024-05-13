#include "reader.hpp"
#include "sudoku.hpp"
#include "workspace.hpp"
#include <cctype>
#include <cmath>
#include <cstdint>
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

bool is_readable(const std::string &extension);
fs::path find_file(const std::string &filename);

std::vector<std::string> search_problems() {
  if (!cwd.has_value()) {
    std::exit(201);
  };

  std::vector<std::string> files;

  for (auto entry : fs::directory_iterator(cwd.value() / INPUT)) {
    std::string extension = entry.path().extension();

    if (is_readable(extension)) {
      files.push_back(entry.path().filename());
    }
  };

  return files;
};

std::optional<sudoku::sudoku*> read_sheet(std::string &filename) {
  fs::path filepath = find_file(filename);
  auto *sheet = new std::vector<uint8_t>(std::pow(9, 2));

  std::ifstream file;
  file.open(filepath);

  char chr;
  std::size_t i = 0;

  while (file.get(chr)) {
    if (std::isdigit(chr)) {
      (*sheet)[i++] = chr - '0';
    };
  };

  file.close();
  if (sheet->size() != sheet->capacity()) {
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

bool is_readable(const std::string &extension) {
  return extension.compare("txt");
};

} // namespace reader
