#include "solver.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <vector>

void feed_solver_test(solver::Solver &solver);
void solve_solver_test();

int main() {
  solver::Solver solver;

  feed_solver_test(solver);
  return 0;
}

void feed_solver_test(solver::Solver &solver) {
  std::vector<short> problem(std::pow(9, 2), 0);
  std::vector<bool> expect(std::pow(9, 3), true);
  std::vector<std::array<int, 2>> fill;
  const short value = 1;
  fill.push_back({0, 0});
  fill.push_back({3, 1});
  fill.push_back({6, 2});

  fill.push_back({1, 3});
  fill.push_back({4, 4});
  fill.push_back({7, 5});

  fill.push_back({2, 6});
  fill.push_back({5, 7});
  fill.push_back({8, 8});

  for (const auto &coor : fill) {
    int idx = coor[0] + coor[1] * 9;
    problem[idx] = value;

    idx = coor[0] * 9 + coor[1] * std::pow(9, 2);
    solver::BlockIt blockIt = idx;
    solver::RowIt rowIt = idx;
    solver::ColumnIt columnIt = idx;
    std::vector<solver::It *> iterators = {&blockIt, &rowIt, &columnIt};

    for (const auto &it : iterators) {
      for (int target = it->next(); target != -1; target = it->next()) {
        if (target != idx) {
          expect[target + value - 1] = false;
        }
      }
    }
  }

  solver.feed(problem);

  assert(expect.size() == solver.sheet.size());
  for (int i = 0; i < expect.size(); ++i) {
    assert(expect[i] == solver.sheet[i]);
  }
}
