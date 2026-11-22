#include "front/resource/resource.hpp"

namespace front {
std::filesystem::path ResourceManager::resource_directory_;

void ResourceManager::set_resource_directory(
    const std::filesystem::path &path) {
    resource_directory_ = std::filesystem::absolute(path);
}

std::filesystem::path
ResourceManager::resolve(const std::filesystem::path &path) {
    if (path.is_absolute())
        return path;

    return resource_directory_ / path;
}

} // namespace front