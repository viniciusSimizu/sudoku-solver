#include "solver.hpp"
#include <cassert>
#include <cmath>
#include <vector>

void block_test();
void row_test();
void column_test();

int get_idx(int x, int y);

int main() {
  block_test();
  row_test();
  column_test();
  return 0;
}

void block_test() {
  std::vector<int *> cases;
  std::vector<int *> expect;

  for (int i = 0; i < 9; ++i) {
    int block_x = i % 3;
    int block_y = i / 3;
    int *coor = new int[2];
    coor[0] = block_x * 3 + block_x;
    coor[1] = block_y * 3 + block_y;
    cases.push_back(coor);

    int *block = new int[18];
    for (int j = 0; j < 9; ++j) {
      int column = j % 3;
      int row = j / 3;
      block[j * 2] = block_x * 3 + column;
      block[j * 2 + 1] = block_y * 3 + row;
    }
    expect.push_back(block);
  }

  for (int i = 0; i < cases.size(); ++i) {
    int *coor = cases[i];
    int *block = expect[i];

    solver::BlockIt it = coor[1] * std::pow(9, 2) + coor[0] * 9;

    for (int j = 0; j < 9; ++j) {
      int x = block[j * 2];
      int y = block[j * 2 + 1];
      assert(get_idx(x, y) == it.next());
    }
    assert(it.next() == -1);

    delete[] coor;
    delete[] block;
  }
}

void row_test() {
  std::vector<int *> cases;
  std::vector<int *> expect;

  for (int i = 0; i < 9; ++i) {
    int *coor = new int[2];
    coor[0] = coor[1] = i;
    cases.push_back(coor);

    int *row = new int[10];
    row[0] = i;
    for (int j = 0; j < 9; ++j) {
      row[j + 1] = j;
    }
    expect.push_back(row);
  }

  for (int i = 0; i < cases.size(); ++i) {
    int *coor = cases[i];
    int *x = expect[i];
    int y = x[0];
    solver::RowIt it = get_idx(coor[0], coor[1]);

    for (int j = 0; j < 9; ++j) {
      assert(get_idx(x[j + 1], y) == it.next());
    }
    assert(it.next() == -1);

    delete[] coor;
    delete[] x;
  }
}

void column_test() {
  std::vector<int *> cases;
  std::vector<int *> expect;

  for (int i = 0; i < 9; ++i) {
    int *coor = new int[2];
    coor[0] = coor[1] = i;
    cases.push_back(coor);

    int *column = new int[10];
    column[0] = i;
    for (int j = 0; j < 9; ++j) {
      column[j + 1] = j;
    }
    expect.push_back(column);
  }

  for (int i = 0; i < cases.size(); ++i) {
    int *coor = cases[i];
    int *y = expect[i];
    int x = y[0];
    solver::ColumnIt it = get_idx(coor[0], coor[1]);

    for (int j = 0; j < 9; ++j) {
      assert(get_idx(x, y[j + 1]) == it.next());
    }
    assert(it.next() == -1);

    delete[] coor;
    delete[] y;
  }
}

int get_idx(int x, int y) { return x * 9 + y * std::pow(9, 2); }
