#include <frontend/screen_manager.hpp>
#include <frontend/screen.hpp>
#include <front/window/window.hpp>

ScreenManager::ScreenManager(front::Window& window) : window_(window) {}
ScreenManager::~ScreenManager() = default;

void ScreenManager::show(std::unique_ptr<Screen> screen) {
    window_.root().clear();
    current_ = std::move(screen);
    if (current_)
        current_->render(window_.root());
    window_.redraw();
}
