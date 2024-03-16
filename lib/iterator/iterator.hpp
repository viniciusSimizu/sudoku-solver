#pragma once

#include <cstdint>

namespace iterator {
struct It {
public:
  virtual int8_t next() = 0;

protected:
  uint8_t curr, x, y;
  It() : curr(0), x(0), y(0){};
};

struct BlockIt : It {
public:
  BlockIt(uint8_t idx_2d);
  int8_t next();
};

struct RowIt : It {
public:
  RowIt(uint8_t idx_2d);
  int8_t next();
};

struct ColumnIt : It {
public:
  ColumnIt(uint8_t idx_2d);
  int8_t next();
};
} // namespace iterator
