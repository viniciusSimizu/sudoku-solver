#include "workspace.hpp"
#include <algorithm>
#include <optional>
#include <vector>

namespace {
std::vector<std::string> references = {".git/", "build/", "main.cpp"};
}; // namespace

namespace fs = std::filesystem;

std::optional<fs::path> find_workspace() {
  for (auto path = fs::current_path(); path != fs::path("/");
       path = path.parent_path()) {
    for (auto entry : fs::directory_iterator(path)) {
      auto filename = entry.path().filename();
      auto it = std::find(references.begin(), references.end(), filename);

      if (it != references.end()) {
        return path;
      }
    }
  }

  return std::nullopt;
}
