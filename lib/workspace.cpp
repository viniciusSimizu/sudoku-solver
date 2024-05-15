#include "workspace.hpp"
#include <filesystem>
#include <optional>
#include <vector>

namespace {
std::vector<std::string> references = {".git/", "build/", "main.cpp"};
}; // namespace

namespace fs = std::filesystem;

std::optional<fs::path> find_workspace() {
  fs::path path = __FILE__;

  while (path != fs::path("/")) {
    path = path.parent_path();

    for (fs::directory_entry entry : fs::directory_iterator(path)) {
      std::string filename = entry.path().filename();

      for (const std::string &root_ref : references) {
        if (root_ref.compare(filename) == 0) {
          return path;
        };
      };
    };
  };

  return std::nullopt;
}
