#include "solver.hpp"
#include <cmath>
#include <vector>

namespace solver {

int get_start(int idx);
int get_offset_x(int idx, int x);
int get_offset_y(int idx, int y);
int get_offset_xy(int idx, int x, int y);
void mark_block(int idx, bool value, std::vector<bool> &sheet);
void mark_line(int idx, bool value, std::vector<bool> &sheet);
void mark_column(int idx, bool value, std::vector<bool> &sheet);

Solver::Solver() : sheet(std::vector<bool>(std::pow(9, 3))) {}
void Solver::feed(std::vector<short> problem) {
  for (int i = 0; i < sheet.size(); ++i) {
    sheet[i] = true;
  }

  for (int i = 0; i < problem.size(); ++i) {
    short value = problem[i];

    if (value == 0) {
      continue;
    }

    int idx = i * 9 + value - 1;
    mark_block(idx, false, sheet);
    mark_line(idx, false, sheet);
    mark_column(idx, false, sheet);
  }
}

int get_start(int idx) { return std::floor(idx / 9) * 9; }
int get_offset_x(int idx, int x) { return idx + x * 9; }
int get_offset_y(int idx, int y) { return idx + y * std::pow(9, 2); }
int get_offset_xy(int idx, int x, int y) {
  return get_offset_y(get_offset_x(idx, x), y);
}

void mark_block(int idx, bool value, std::vector<bool> &sheet) {
  int x = int(idx / 3 * 9) % 3;
  int y = int(idx / std::pow(9, 2) * 3) % 3;
  int z = idx % 9;

  int begin = get_offset_xy(z, x, y);

  for (int w = 0; w < 3; ++w) {
    for (int h = 0; h < 3; ++h) {
      int target = get_offset_xy(begin, w, h);

      if (target != idx) {
        sheet[target] = false;
      }
    }
  }
}

void mark_line(int idx, bool value, std::vector<bool> &sheet) {
  int y = idx / std::pow(9, 2);
  int z = idx % 9;

  int begin = get_offset_y(z, y);

  for (int w = 0; w < 9; ++w) {
    int target = get_offset_x(begin, w);

    if (target != idx) {
      sheet[target] = false;
    }
  }
}
void mark_column(int idx, bool value, std::vector<bool> &sheet) {
  int x = int(idx / 9) % 9;
  int z = idx % 9;

  int begin = get_offset_x(z, x);

  for (int h = 0; h < 9; ++h) {
    int target = get_offset_y(begin, h);

    if (target != idx) {
      sheet[target] = false;
    }
  }
}
}; // namespace solver
