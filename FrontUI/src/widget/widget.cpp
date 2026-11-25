#include "../backend/backend.hpp"
#include <algorithm>
#include <front/widget/widget.hpp>
namespace front {
struct Widget::Impl {
    detail::backend::Handle native{};
    int x{}, y{}, w{}, h{};
    bool visible{true}, enabled{true};
};
Widget::Widget(void *n) : impl_(std::make_unique<Impl>()) { impl_->native = n; }
Widget::~Widget() = default;
void *Widget::native_handle() const noexcept { return impl_->native; }
void Widget::attach_native(void *n) {
    impl_->native = n;
    apply_geometry();
    detail::backend::widget_show(n, impl_->visible);
    detail::backend::widget_enable(n, impl_->enabled);
}
void Widget::apply_geometry() {
    detail::backend::widget_geometry(impl_->native, impl_->x, impl_->y,
                                     impl_->w, impl_->h);
}
void Widget::set_position(Point p) {
    impl_->x = p.x;
    impl_->y = p.y;
    apply_geometry();
}
void Widget::set_size(Size s) {
    impl_->w = std::max(0, s.width);
    impl_->h = std::max(0, s.height);
    apply_geometry();
}
Point Widget::position() const noexcept { return {impl_->x, impl_->y}; }
Size Widget::size() const noexcept { return {impl_->w, impl_->h}; }
Rect Widget::bounds() const noexcept {
    return {impl_->x, impl_->y, impl_->w, impl_->h};
}
void Widget::show() {
    impl_->visible = true;
    detail::backend::widget_show(impl_->native, true);
}
void Widget::hide() {
    impl_->visible = false;
    detail::backend::widget_show(impl_->native, false);
}
void Widget::set_visible(bool v) { v ? show() : hide(); }
bool Widget::visible() const noexcept { return impl_->visible; }
void Widget::set_enabled(bool e) {
    impl_->enabled = e;
    detail::backend::widget_enable(impl_->native, e);
}
bool Widget::enabled() const noexcept { return impl_->enabled; }
void Widget::redraw() { detail::backend::widget_redraw(impl_->native); }
} // namespace front
