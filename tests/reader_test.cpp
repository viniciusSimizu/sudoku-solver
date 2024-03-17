#include "reader.hpp"
#include "workspace.hpp"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using reader::Reader;

void find_problems_test(Reader &reader);
void read_problems_test(Reader &reader);

std::vector<uint8_t> read_problem(const std::string &file);
bool has_case(std::string &file);

const static auto path = workspace::get_workspace() / "input";
const static std::vector<std::string> entries = {path / "case1.txt",
                                                 path / "case2.txt"};

int main() {
  Reader reader;

  find_problems_test(reader);
  read_problems_test(reader);

  return 0;
}

void find_problems_test(Reader &reader) {
  reader.read_dir();
  auto items = reader.todo;

  for (auto item = items.front(); !items.empty(); item = items.front()) {
    std::string file = item;
    assert(has_case(file));
    items.pop();
  }
}

void read_problems_test(Reader &reader) {
  reader.read_dir();
  auto items = reader.todo;

  for (auto item = items.front(); !items.empty(); item = items.front()) {
    assert(reader::read_problem(item).sheet == read_problem(item));
    items.pop();
  }
}

std::vector<uint8_t> read_problem(const std::string &file) {
  std::ifstream out;
  std::vector<uint8_t> sheet(9 * 9);
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
