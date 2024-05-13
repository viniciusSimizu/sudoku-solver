#include "reader.hpp"
#include "solver.hpp"
#include "sudoku.hpp"
#include "writer.hpp"

int main() {
  std::vector<std::string> files = reader::search_problems();

  for (std::string file : files) {
    std::optional<sudoku::sudoku *> data = reader::read_sheet(file);

    if (!data.has_value()) {
      continue;
    };

    solver::solve(*data.value());
    writer::save(*data.value());

    sudoku::free(data.value());
  };
}
