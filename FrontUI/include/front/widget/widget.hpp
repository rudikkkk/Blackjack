#pragma once
#include "../core/types.hpp"
#include <memory>

namespace front {
class Group;
class Label;
class Button;
class Image;
class NumberInput;
class Window;

class Widget {
  public:
    virtual ~Widget();
    Widget(const Widget &) = delete;
    Widget &operator=(const Widget &) = delete;
    Widget(Widget &&) = delete;
    Widget &operator=(Widget &&) = delete;
    void set_position(Point);
    virtual void set_size(Size);
    Point position() const noexcept;
    Size size() const noexcept;
    Rect bounds() const noexcept;
    void show();
    void hide();
    void set_visible(bool);
    bool visible() const noexcept;
    void set_enabled(bool);
    bool enabled() const noexcept;
    void redraw();

  protected:
    explicit Widget(void *native = nullptr);
    void attach_native(void *);
    void apply_geometry();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    void *native_handle() const noexcept;
    friend class Group;
    friend class Window;
    friend class Label;
    friend class Button;
    friend class Image;
    friend class NumberInput;
class NumberInput;
};
} // namespace front
