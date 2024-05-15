#include "reader.hpp"
#include "solver.hpp"
#include "sudoku.hpp"
#include "writer.hpp"

int main() {
  std::vector<sudoku::sudoku *> cases = reader::search_problems();

  for (sudoku::sudoku *case_ : cases) {
    solver::solve(*case_);
    writer::save(*case_);

    sudoku::free(case_);
  };
}
