#include "writer.hpp"
#include "logger.hpp"
#include "workspace.hpp"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>

namespace writer {

namespace fs = std::filesystem;

std::optional<fs::path> cwd = find_workspace();

void save(sudoku::sudoku &data) {
  logger::info("saving " + *data.filename);

  if (!cwd.has_value()) {
    logger::error("workspace not found");
    std::exit(201);
  };

  std::string filename = *data.filename + ENDING;
  fs::path filepath = cwd.value() / OUTPUT / filename;

  std::ofstream file;
  file.open(filepath);

  if (!data.solved) {
    file << "unsolvable\n\n";
  };

  uint8_t i = 0;

  while (true) {
    file << (*data.sheet)[i++];

    if (i >= std::pow(9, 2))
      break;

    uint8_t x = i % 9;
    uint8_t y = i / 9;

    if (x != 0) {
      file << '|';
    };

    if (x == 0) {
      file << '\n';
    };

    if (x == 0 && y % 3 == 0) {
      file << "===========\n";
    };
  };

  file.close();
  logger::info("saving [finished]");
}

}; // namespace writer
