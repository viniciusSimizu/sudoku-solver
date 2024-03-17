#include "workspace.hpp"
#include <algorithm>
#include <vector>

namespace workspace {

namespace fs = std::filesystem;

fs::path get_workspace() {
  std::vector<std::string> references = {".git/", "build/", "main.cpp"};

  for (auto curr = fs::current_path(); curr != fs::path("/");
       curr = curr.parent_path()) {

    for (auto entry : fs::directory_iterator(curr)) {
      auto filename = entry.path().filename();
      auto find = std::find(references.begin(), references.end(), filename);

      if (find != references.end()) {
        return curr;
      }
    }
  }

  return fs::current_path();
}
}; // namespace workspace
