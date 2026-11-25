#pragma once
#include "../widget/group.hpp"
#include <memory>
#include <functional>
#include <string>
#include <utility>

namespace front {

class Window {
  public:
    Window(int width, int height, std::string title);
    ~Window();
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Group &root() noexcept;
    template <class T, class... Args> T &create(Args &&...args) {
        return root_.create<T>(std::forward<Args>(args)...);
    }
    void set_title(const std::string &);
    void set_size(Size);
    void set_resizable(bool = true);
    void show();
    void hide();
    void redraw();
    void run();
    void close();
    void post(std::function<void()> callback);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    Group root_;
};
} // namespace front
