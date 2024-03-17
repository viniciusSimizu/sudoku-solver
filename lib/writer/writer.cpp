#include "writer.hpp"
#include "workspace.hpp"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace writer {
const static std::string ending = "_solved";
const static std::string extension = ".txt";
const static std::string output_dir = "output";

void save(std::vector<uint8_t> &sheet, const std::string &name) {
  std::string path = output_dir + '/' + name + ending + extension;
  std::string filepath = workspace::get_workspace() / path;
  std::ofstream file;

  file.open(filepath);

  for (uint8_t idx_2d = 0; idx_2d < pow(9, 2); ++idx_2d) {
    uint8_t x = idx_2d % 9;
    uint8_t y = idx_2d / 9;

    if (y != 0 && x == 0) {
      file << '\n';
    }

    if (y != 0 && y % 3 == 0 && x == 0) {
      file << "===========\n";
    }

    if (x != 0 && x % 3 == 0) {
      file << '|';
    }

    file << (int)sheet[idx_2d];
  }

  file.close();
}
}; // namespace writer
