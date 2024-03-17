#include "reader.hpp"
#include "workspace.hpp"
#include "writer.hpp"
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

using reader::Reader;

std::vector<uint8_t> get_case_1();

int main() {
  auto problem = get_case_1();
  std::string name = "case_1";
  writer::save(problem, name);
  std::string filepath =
      workspace::get_workspace() / "output" / (name + "_solved.txt");

  Reader reader;
  auto result = reader::read_problem(filepath).sheet;

  assert(result.size() == problem.size());
  for (int i = 0; i < result.size(); ++i) {
    assert(result[i] == problem[i]);
  }

  return 0;
}

std::vector<uint8_t> get_case_1() {
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

  return case_;
}
