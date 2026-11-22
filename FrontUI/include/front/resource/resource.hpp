#pragma once
#include <filesystem>

namespace front {
class ResourceManager {
  public:
    static void set_resource_directory(const std::filesystem::path &path);

    static std::filesystem::path resolve(const std::filesystem::path &path);

  private:
    static std::filesystem::path resource_directory_;
};
} // namespace front