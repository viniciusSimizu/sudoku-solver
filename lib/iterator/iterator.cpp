#include "iterator.hpp"
#include <cstdint>

namespace iterator {
BlockIt::BlockIt(uint8_t idx_2d) : It() {
  x = uint8_t((idx_2d % 9) / 3) * 3;
  y = uint8_t((idx_2d / 9) / 3) * 3;
}

int8_t BlockIt::next() {
  if (curr >= 9) {
    return -1;
  }

  int8_t column = curr % 3;
  int8_t row = curr / 3;
  ++curr;

  return x + column + (y + row) * 9;
}

RowIt::RowIt(uint8_t idx_2d) { y = idx_2d / 9; }

int8_t RowIt::next() {
  if (curr >= 9) {
    return -1;
  }
  return curr++ + y * 9;
}

ColumnIt::ColumnIt(uint8_t idx_2d) { x = idx_2d % 9; }

int8_t ColumnIt::next() {
  if (curr >= 9) {
    return -1;
  }
  return x + curr++ * 9;
}
} // namespace iterator
