#include "iterator.hpp"
#include <cstdint>

namespace iterator {

int8_t to_idx(uint8_t x, uint8_t y);

BlockIt::BlockIt(uint8_t idx) : It() {
  x = uint8_t((idx % 9) / 3) * 3;
  y = uint8_t((idx / 9) / 3) * 3;
}

int8_t BlockIt::next() {
  if (count >= 9) {
    return -1;
  }

  uint8_t column = count % 3;
  uint8_t row = count / 3;
  ++count;

	return to_idx(x + column, y + row);
}

RowIt::RowIt(uint8_t idx_2d) { y = idx_2d / 9; }

int8_t RowIt::next() {
  if (count >= 9) {
    return -1;
  }
	return to_idx(count++, y);
}

ColumnIt::ColumnIt(uint8_t idx_2d) { x = idx_2d % 9; }

int8_t ColumnIt::next() {
  if (count >= 9) {
    return -1;
  }
	return to_idx(x, count++);
}

int8_t to_idx(uint8_t x, uint8_t y) {
	return y * 9 + x;
};

} // namespace iterator
