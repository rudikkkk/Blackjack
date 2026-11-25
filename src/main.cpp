#include <frontend/app.hpp>
#include <front/resource/resource.hpp>

#ifndef ASSETS_DIR
#define ASSETS_DIR "assets"
#endif

int main() {
    front::ResourceManager::set_resource_directory(ASSETS_DIR);
    App app;
    app.run();
    return 0;
}
