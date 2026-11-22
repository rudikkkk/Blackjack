#pragma once
#include "../layout/layout.hpp"
#include "widget.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace front {
class Group : public Widget {
  public:
    explicit Group(Size size = {100, 100});
    ~Group() override;
    Widget &add(std::unique_ptr<Widget>);
    template <class T, class... Args> T &create(Args &&...args) {
        auto p = std::make_unique<T>(std::forward<Args>(args)...);
        T &ref = *p;
        add(std::move(p));
        return ref;
    }
    void remove(Widget &);
    void clear();
    void set_layout(std::unique_ptr<Layout>);
    void update_layout();
    const std::vector<std::unique_ptr<Widget>> &children() const noexcept;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    void *native_group() const noexcept;
    friend class Window;
};
} // namespace front
