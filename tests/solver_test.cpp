#include "iterator.hpp"
#include "solver.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace iterator;
using solver::Solver;

template <typename T> struct Problem {
  std::vector<uint8_t> case_;
  std::vector<T> expect;
};

void feed_solver_test(Solver &solver);
Problem<bool> feed_solver_test_case_1_resolved();
Problem<bool> feed_solver_test_case_2_partial();
Problem<bool> feed_solver_test_case_3_invalid();

std::vector<uint8_t> solve_solver_test(Solver &solver);
Problem<uint8_t> solve_solver_test_case();

void export_solver_test(Solver &solver, const std::vector<uint8_t> &expect);

std::vector<bool> build_expected(const std::vector<uint8_t> &case_);
uint8_t get_2d_idx(uint8_t x, uint8_t y);
uint16_t get_3d_idx(uint8_t x, uint8_t y);
uint16_t get_2d_to_3d_idx(uint8_t idx_2d);

int main() {
  Solver solver;

  feed_solver_test(solver);
  auto expect = solve_solver_test(solver);
  export_solver_test(solver, expect);

  return 0;
}

void feed_solver_test(Solver &solver) {
  Problem problem = feed_solver_test_case_1_resolved();
  solver.feed(problem.case_);
  assert(solver.solvable);
  assert(solver.sheet.size() == problem.expect.size());
  for (int i = 0; i < problem.expect.size(); ++i) {
    assert(solver.sheet[i] == problem.expect[i]);
  }

  problem = feed_solver_test_case_2_partial();
  solver.feed(problem.case_);
  assert(solver.solvable);
  assert(solver.sheet.size() == problem.expect.size());
  for (int i = 0; i < problem.expect.size(); ++i) {
    if (solver.sheet[i] != problem.expect[i]) {
    }
    assert(solver.sheet[i] == problem.expect[i]);
  }

  problem = feed_solver_test_case_3_invalid();
  solver.feed(problem.case_);
  assert(!solver.solvable);
}

std::vector<uint8_t> solve_solver_test(Solver &solver) {
  auto problem = solve_solver_test_case();
  auto expect = build_expected(problem.expect);

  solver.feed(problem.case_);
  solver.solve();

  assert(solver.solvable);
  assert(solver.sheet.size() == expect.size());
  for (int i = 0; i < expect.size(); ++i) {
    assert(solver.sheet[i] == expect[i]);
  }

  return problem.expect;
}

void export_solver_test(Solver &solver, const std::vector<uint8_t> &expect) {
  auto result = solver.export_();
  assert(result.size() == expect.size());
  for (int idx_2d = 0; idx_2d < expect.size(); ++idx_2d) {
    assert(result[idx_2d] == expect[idx_2d]);
  }
}

Problem<bool> feed_solver_test_case_1_resolved() {
  Problem<bool> problem;
  std::vector<uint8_t> case_;

  // 1 2 3 7 8 9 4 5 6
  // 4 5 6 1 2 3 7 8 9
  // 7 8 9 4 5 6 1 2 3
  // 3 1 2 9 7 8 6 4 5
  // 6 4 5 3 1 2 9 7 8
  // 9 7 8 6 4 5 3 1 2
  // 2 3 1 8 9 7 5 6 4
  // 5 6 4 2 3 1 8 9 7
  // 8 9 7 5 6 4 2 3 1

  case_.insert(case_.end(), {1, 2, 3, 7, 8, 9, 4, 5, 6});
  case_.insert(case_.end(), {4, 5, 6, 1, 2, 3, 7, 8, 9});
  case_.insert(case_.end(), {7, 8, 9, 4, 5, 6, 1, 2, 3});
  case_.insert(case_.end(), {3, 1, 2, 9, 7, 8, 6, 4, 5});
  case_.insert(case_.end(), {6, 4, 5, 3, 1, 2, 9, 7, 8});
  case_.insert(case_.end(), {9, 7, 8, 6, 4, 5, 3, 1, 2});
  case_.insert(case_.end(), {2, 3, 1, 8, 9, 7, 5, 6, 4});
  case_.insert(case_.end(), {5, 6, 4, 2, 3, 1, 8, 9, 7});
  case_.insert(case_.end(), {8, 9, 7, 5, 6, 4, 2, 3, 1});

  problem.case_ = case_;
  problem.expect = build_expected(case_);
  return problem;
}

Problem<bool> feed_solver_test_case_2_partial() {
  Problem<bool> problem;
  std::vector<uint8_t> case_(pow(9, 2), 0);

  // 7 x x x x x 1 x x
  // x 9 x x 4 x x x x
  // x x x x x x x x 3
  // 1 x x 2 x x 5 7 x
  // x x x x x x x x x
  // x x x x x 8 x x x
  // x 7 x x x 9 x x x
  // x x x 5 x x x x 6
  // 3 x x x x x x x 8

  case_[get_2d_idx(0, 0)] = 7;
  case_[get_2d_idx(6, 0)] = 1;
  case_[get_2d_idx(1, 1)] = 9;
  case_[get_2d_idx(4, 1)] = 4;
  case_[get_2d_idx(8, 2)] = 3;
  case_[get_2d_idx(0, 3)] = 1;
  case_[get_2d_idx(3, 3)] = 2;
  case_[get_2d_idx(6, 3)] = 5;
  case_[get_2d_idx(7, 3)] = 7;
  case_[get_2d_idx(5, 5)] = 8;
  case_[get_2d_idx(1, 6)] = 7;
  case_[get_2d_idx(5, 6)] = 9;
  case_[get_2d_idx(3, 7)] = 5;
  case_[get_2d_idx(8, 7)] = 6;
  case_[get_2d_idx(0, 8)] = 3;
  case_[get_2d_idx(8, 8)] = 8;

  problem.case_ = case_;
  problem.expect = build_expected(case_);
  return problem;
}

Problem<bool> feed_solver_test_case_3_invalid() {
  Problem<bool> problem;
  std::vector<uint8_t> case_(pow(9, 2), 0);

  // x x x x x x 1 1 x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x
  // x x x x x x x x x

  case_[6] = 1;
  case_[7] = 1;

  problem.case_ = case_;
  return problem;
}

Problem<uint8_t> solve_solver_test_case() {
  Problem<uint8_t> problem;

  std::vector<uint8_t> case_;

  // x 2 3 7 8 9 4 5 6
  // 4 x 6 1 2 3 7 8 9
  // 7 8 x 4 5 6 1 2 3
  // 3 1 2 x 7 8 6 4 5
  // 6 4 5 3 x 2 9 7 8
  // 9 7 8 6 4 x 3 1 2
  // 2 3 1 8 9 7 x 6 4
  // 5 6 4 2 3 1 8 x 7
  // 8 9 7 5 6 4 2 3 x

  case_.insert(case_.end(), {0, 2, 3, 7, 8, 9, 4, 5, 6});
  case_.insert(case_.end(), {4, 0, 6, 1, 2, 3, 7, 8, 9});
  case_.insert(case_.end(), {7, 8, 0, 4, 5, 6, 1, 2, 3});
  case_.insert(case_.end(), {3, 1, 2, 0, 7, 8, 6, 4, 5});
  case_.insert(case_.end(), {6, 4, 5, 3, 0, 2, 9, 7, 8});
  case_.insert(case_.end(), {9, 7, 8, 6, 4, 0, 3, 1, 2});
  case_.insert(case_.end(), {2, 3, 1, 8, 9, 7, 0, 6, 4});
  case_.insert(case_.end(), {5, 6, 4, 2, 3, 1, 8, 0, 7});
  case_.insert(case_.end(), {8, 9, 7, 5, 6, 4, 2, 3, 0});

  std::vector<uint8_t> expect;

  // 1 2 3 7 8 9 4 5 6
  // 4 5 6 1 2 3 7 8 9
  // 7 8 9 4 5 6 1 2 3
  // 3 1 2 9 7 8 6 4 5
  // 6 4 5 3 1 2 9 7 8
  // 9 7 8 6 4 5 3 1 2
  // 2 3 1 8 9 7 5 6 4
  // 5 6 4 2 3 1 8 9 7
  // 8 9 7 5 6 4 2 3 1

  expect.insert(expect.end(), {1, 2, 3, 7, 8, 9, 4, 5, 6});
  expect.insert(expect.end(), {4, 5, 6, 1, 2, 3, 7, 8, 9});
  expect.insert(expect.end(), {7, 8, 9, 4, 5, 6, 1, 2, 3});
  expect.insert(expect.end(), {3, 1, 2, 9, 7, 8, 6, 4, 5});
  expect.insert(expect.end(), {6, 4, 5, 3, 1, 2, 9, 7, 8});
  expect.insert(expect.end(), {9, 7, 8, 6, 4, 5, 3, 1, 2});
  expect.insert(expect.end(), {2, 3, 1, 8, 9, 7, 5, 6, 4});
  expect.insert(expect.end(), {5, 6, 4, 2, 3, 1, 8, 9, 7});
  expect.insert(expect.end(), {8, 9, 7, 5, 6, 4, 2, 3, 1});

  problem.case_ = case_;
  problem.expect = expect;
  return problem;
}

std::vector<bool> build_expected(const std::vector<uint8_t> &case_) {
  std::vector<bool> expect(pow(9, 3), true);

  for (uint8_t idx_2d = 0; idx_2d < case_.size(); ++idx_2d) {
    uint8_t z = case_[idx_2d];
    if (z == 0) {
      continue;
    }

    uint16_t idx_3d = get_2d_to_3d_idx(idx_2d);
    BlockIt blockIt = idx_2d;
    RowIt rowIt = idx_2d;
    ColumnIt columnIt = idx_2d;
    std::vector<It *> iterators = {&blockIt, &rowIt, &columnIt};

    for (int i = 0; i < 9; ++i) {
      if (i + 1 != z) {
        expect[idx_3d + i] = false;
      }
    }

    for (const auto &it : iterators) {
      for (int8_t curr = it->next(); curr != -1; curr = it->next()) {
        if (curr != idx_2d) {
          idx_3d = get_2d_to_3d_idx(curr);
          expect[idx_3d + z - 1] = false;
        }
      }
    }
  }

  return expect;
}

uint8_t get_2d_idx(uint8_t x, uint8_t y) { return x + y * 9; }
uint16_t get_3d_idx(uint8_t x, uint8_t y) { return x * 9 + y * pow(9, 2); }
uint16_t get_2d_to_3d_idx(uint8_t idx_2d) {
  uint8_t x = idx_2d % 9;
  uint8_t y = idx_2d / 9;
  return get_3d_idx(x, y);
}
