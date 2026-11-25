#pragma once
#include <memory>

class Screen;
namespace front { class Window; }

class ScreenManager {
public:
    explicit ScreenManager(front::Window& window);
    ~ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    void show(std::unique_ptr<Screen> screen);
private:
    front::Window& window_;
    std::unique_ptr<Screen> current_;
};
