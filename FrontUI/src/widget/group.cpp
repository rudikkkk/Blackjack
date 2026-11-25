#include "../backend/backend.hpp"
#include <algorithm>
#include <front/widget/group.hpp>
#include <stdexcept>
namespace front {
struct Group::Impl {
    void *native{};
    std::vector<std::unique_ptr<Widget>> children;
    std::unique_ptr<Layout> layout;
};
Group::Group(Size s) : Widget(nullptr), impl_(std::make_unique<Impl>()) {
    impl_->native = detail::backend::create_group(0, 0, s.width, s.height);
    attach_native(impl_->native);
    set_size(s);
}
Group::~Group() {
    clear();
    detail::backend::destroy_widget(impl_->native);
    impl_->native = nullptr;
}
void *Group::native_group() const noexcept { return impl_->native; }
Widget &Group::add(std::unique_ptr<Widget> c) {
    if (!c)
        throw std::invalid_argument("null child");
    if (c->native_handle())
        detail::backend::group_add(impl_->native, c->native_handle());
    impl_->children.push_back(std::move(c));
    update_layout();
    return *impl_->children.back();
}
void Group::remove(Widget &c) {
    auto it = std::find_if(impl_->children.begin(), impl_->children.end(),
                           [&](auto &p) { return p.get() == &c; });
    if (it == impl_->children.end())
        return;
    if (c.native_handle()) {
        detail::backend::group_remove(impl_->native, c.native_handle());
        if (dynamic_cast<Group *>(&c) == nullptr) {
            detail::backend::destroy_widget(c.native_handle());
            c.attach_native(nullptr);
        }
    }
    impl_->children.erase(it);
    update_layout();
}
void Group::clear() {
    for (auto &c : impl_->children)
        if (c->native_handle()) {
            detail::backend::group_remove(impl_->native, c->native_handle());
            if (dynamic_cast<Group *>(c.get()) == nullptr) {
                detail::backend::destroy_widget(c->native_handle());
                c->attach_native(nullptr);
            }
        }
    impl_->children.clear();
    update_layout();
}
void Group::set_layout(std::unique_ptr<Layout> l) {
    impl_->layout = std::move(l);
    update_layout();
}
void Group::update_layout() {
    if (impl_->layout) {
        auto s = size();
        impl_->layout->arrange(*this, {0, 0, s.width, s.height});
    }
}
const std::vector<std::unique_ptr<Widget>> &Group::children() const noexcept {
    return impl_->children;
}
} // namespace front
