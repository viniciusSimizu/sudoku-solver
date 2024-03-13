#include "reader.hpp"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> find_problems_test(reader::Reader &reader);
void read_problems_test(reader::Reader &reader,
                        std::vector<std::string> &cases);
std::vector<short> read_problem(std::string &file);
bool has_case(std::string &file);

const static auto path = reader::get_workspace() / "input";
const static std::vector<std::string> entries = {path / "case1.txt",
                                                 path / "case2.txt"};

int main() {
  reader::Reader reader;

  auto cases = find_problems_test(reader);
  read_problems_test(reader, cases);

  return 0;
}

std::vector<std::string> find_problems_test(reader::Reader &reader) {
  std::vector<std::string> cases;

  for (auto item = reader.get(); item.has_value();
       ++reader, item = reader.get()) {

    std::string file = item.value();
    cases.push_back(file);
    assert(has_case(file));
  }

  return cases;
}

void read_problems_test(reader::Reader &reader,
                        std::vector<std::string> &cases) {
  for (int i = 0; i < cases.size(); ++i) {
    auto _case = cases[i];
    assert(reader.read_problem(_case) == read_problem(_case));
  }
}

std::vector<short> read_problem(std::string &file) {
  std::ifstream out;
  std::vector<short> sheet(9 * 9);
  char chr;
  int needle = 0;

  out.open(file, std::ios::out);
  while (out.get(chr)) {
    if (std::isdigit(chr)) {
      sheet[needle++] = chr - '0';
    }
  }

  out.close();
  return sheet;
}

bool has_case(std::string &file) {
  auto find = std::find(entries.begin(), entries.end(), file);
  return find != entries.end();
}
