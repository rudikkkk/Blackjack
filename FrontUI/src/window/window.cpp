#include "../backend/backend.hpp"
#include <front/window/window.hpp>
namespace front {
struct Window::Impl {
    detail::backend::Handle native{};
};
Window::Window(int w, int h, std::string title)
    : impl_(std::make_unique<Impl>()), root_({w, h}) {
    impl_->native = detail::backend::create_window(w, h, title.c_str());
    detail::backend::window_attach_root(impl_->native, root_.native_group());
    detail::backend::window_resizable(impl_->native, true);
}
Window::~Window() {
    if (impl_->native) {
        detail::backend::window_detach_root(impl_->native,
                                            root_.native_group());
        detail::backend::window_destroy(impl_->native);
        impl_->native = nullptr;
    }
}
Group &Window::root() noexcept { return root_; }
void Window::set_title(const std::string &t) {
    detail::backend::window_title(impl_->native, t.c_str());
}
void Window::set_size(Size s) {
    detail::backend::window_size(impl_->native, s.width, s.height);
    root_.set_size(s);
    root_.update_layout();
}
void Window::set_resizable(bool r) {
    detail::backend::window_resizable(impl_->native, r);
}
void Window::show() { detail::backend::window_show(impl_->native, true); }
void Window::hide() { detail::backend::window_show(impl_->native, false); }
void Window::redraw() { detail::backend::window_redraw(impl_->native); }
void Window::run() { detail::backend::run(); }
void Window::close() { hide(); }
void Window::post(std::function<void()> callback) {
    detail::backend::post(std::move(callback));
}
} // namespace front
