#include "solver.hpp"
#include <cassert>
#include <vector>
void block_iterator_test();
/* void line_iterator_test();
void column_iterator_test(); */

int main() {
  block_iterator_test();
  return 0;
}

void block_iterator_test() {
  std::vector<int *> cases;
  std::vector<int *> expect;

  for (int i = 0; i < 9; ++i) {
    int x = i % 3;
    int y = i / 3;
    int *coor = new int[2];
    coor[0] = x * 3 + x;
    coor[1] = y * 3 + y;
    cases.push_back(coor);

    int *block = new int[18];
    for (int j = 0; j < 9; ++j) {
      int column = j % 3;
      int line = j / 3;
      block[j * 2] = x * 3 + column;
      block[j * 2 + 1] = y * 3 + line;
    }
    expect.push_back(block);
  }

  for (int i = 0; i < cases.size(); ++i) {
    int *coor = cases[i];
    int *block = expect[i];
    solver::BlockIt it = solver::get_offset_xy(0, coor[0], coor[1]);

    for (int j = 0; j < 9; ++j) {
      int x = block[j * 2];
      int y = block[(j * 2 + 1)];
      int idx = solver::get_offset_xy(0, x, y);
      assert(idx == it.next());
    }

    delete[] coor;
    delete[] block;
  }
}
