#include "iterator.hpp"
#include <cassert>
#include <cstdint>
#include <vector>

using namespace iterator;

void block_test();
void row_test();
void column_test();

uint8_t get_2d_idx(uint8_t x, uint8_t y);

int main() {
  block_test();
  row_test();
  column_test();
  return 0;
}

void block_test() {
  std::vector<uint8_t> cases;
  std::vector<uint8_t *> expect;

  for (int i = 0; i < 9; ++i) {
    uint8_t *block = new uint8_t[9];
    uint8_t block_x = i % 3;
    uint8_t block_y = i / 3;
    uint8_t x = block_x * 3 + block_x;
    uint8_t y = block_y * 3 + block_y;
    cases.push_back(get_2d_idx(x, y));

    for (int j = 0; j < 9; ++j) {
      uint8_t column = j % 3;
      uint8_t row = j / 3;
      x = block_x * 3 + column;
      y = block_y * 3 + row;
      block[j] = get_2d_idx(x, y);
    }
    expect.push_back(block);
  }

  for (int i = 0; i < cases.size(); ++i) {
    BlockIt it = cases[i];
    uint8_t *block = expect[i];

    for (int j = 0; j < 9; ++j) {
      assert(block[j] == it.next());
    }
    assert(it.next() == -1);

    delete[] block;
  }
}

void row_test() {
  std::vector<uint8_t> cases;
  std::vector<uint8_t *> expect;

  for (int i = 0; i < 9; ++i) {
    cases.push_back(get_2d_idx(i, i));

    uint8_t *row = new uint8_t[9];
    for (int j = 0; j < 9; ++j) {
      row[j] = get_2d_idx(j, i);
    }
    expect.push_back(row);
  }

  for (int i = 0; i < cases.size(); ++i) {
    uint8_t *row = expect[i];
    RowIt it = cases[i];

    for (int j = 0; j < 9; ++j) {
      assert(row[j] == it.next());
    }
    assert(it.next() == -1);

    delete[] row;
  }
}

void column_test() {
  std::vector<uint8_t> cases;
  std::vector<uint8_t *> expect;

  for (int i = 0; i < 9; ++i) {
    cases.push_back(get_2d_idx(i, i));

    uint8_t *column = new uint8_t[9];
    for (int j = 0; j < 9; ++j) {
      column[j] = get_2d_idx(i, j);
    }
    expect.push_back(column);
  }

  for (int i = 0; i < cases.size(); ++i) {
    uint8_t *column = expect[i];
    ColumnIt it = cases[i];

    for (int j = 0; j < 9; ++j) {
      assert(column[j] == it.next());
    }
    assert(it.next() == -1);

    delete[] column;
  }
}

uint8_t get_2d_idx(uint8_t x, uint8_t y) { return x + y * 9; }
