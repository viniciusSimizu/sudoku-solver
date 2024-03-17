#include "reader.hpp"
#include "solver.hpp"
#include "writer.hpp"

using reader::Reader;
using solver::Solver;

int main() {
  Reader reader;
  reader.read_dir();

  Solver solver;

  for (auto case_ = reader.get(); case_.has_value(); case_ = reader.get()) {
    reader::Sudoku sudoku = case_.value();
    solver.feed(sudoku.sheet);
    solver.solve();

    if (!solver.solvable) {
      continue;
    }

    auto solution = solver.export_();
    writer::save(solution, sudoku.name);
  }

  return 0;
}
