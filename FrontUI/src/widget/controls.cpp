#include "../backend/backend.hpp"
#include "front/resource/resource.hpp"
#include <algorithm>
#include <front/widget/controls.hpp>
#include <stdexcept>

namespace front {
struct Label::Impl {
    std::string text;
};
Label::Label(std::string text, Size s)
    : Widget(
          detail::backend::create_label(0, 0, s.width, s.height, text.c_str())),
      impl_(std::make_unique<Impl>()) {
    impl_->text = std::move(text);
    set_size(s);
}
Label::~Label() = default;
void Label::set_text(std::string t) {
    impl_->text = std::move(t);
    detail::backend::label_text(native_handle(), impl_->text.c_str());
    redraw();
}
const std::string &Label::text() const noexcept { return impl_->text; }
void Label::set_text_color(Color c) {
    detail::backend::label_color(native_handle(), c);
    redraw();
}
void Label::set_font_size(int px) {
    detail::backend::label_font_size(native_handle(), px);
    redraw();
}
struct Button::Impl {
    std::string text;
    std::function<void()> callback;
};
Button::Button(std::string text, Size s)
    : Widget(detail::backend::create_button(0, 0, s.width, s.height,
                                            text.c_str(),
                                            [this] {
                                                if (impl_ && impl_->callback)
                                                    impl_->callback();
                                            })),
      impl_(std::make_unique<Impl>()) {
    impl_->text = std::move(text);
    set_size(s);
}
Button::~Button() = default;
void Button::set_text(std::string t) {
    impl_->text = std::move(t);
    detail::backend::button_text(native_handle(), impl_->text.c_str());
    redraw();
}
const std::string &Button::text() const noexcept { return impl_->text; }
void Button::set_on_click(std::function<void()> f) {
    impl_->callback = std::move(f);
}
void Button::set_color(Color c) {
    detail::backend::button_color(native_handle(), c);
    redraw();
}
ImageData::ImageData() = default;
ImageData::ImageData(int w, int h, int c)
    : width_(w), height_(h), channels_(c) {
    if (w <= 0 || h <= 0 || c < 1 || c > 4)
        throw std::invalid_argument("Invalid image dimensions/channels");
    pixels_.resize(size_t(w) * size_t(h) * size_t(c));
}
bool ImageData::load(const std::string &path) {
    detail::backend::ImagePixels decoded;
    auto resolved = ResourceManager::resolve(path);
    if (!detail::backend::image_load(resolved.string(), decoded))
        return false;
    width_ = decoded.width;
    height_ = decoded.height;
    channels_ = decoded.channels;
    pixels_ = std::move(decoded.pixels);
    return true;
}
int ImageData::width() const noexcept { return width_; }
int ImageData::height() const noexcept { return height_; }
int ImageData::channels() const noexcept { return channels_; }
const std::uint8_t *ImageData::data() const noexcept { return pixels_.data(); }
std::uint8_t *ImageData::data() noexcept { return pixels_.data(); }
bool ImageData::empty() const noexcept { return pixels_.empty(); }
struct Image::Impl {
    ImageData data;
    ImageFit fit{ImageFit::contain};
};
Image::Image(Size s)
    : Widget(detail::backend::create_image_widget(0, 0, s.width, s.height)),
      impl_(std::make_unique<Impl>()) {
    set_size(s);
}
Image::~Image() = default;
void Image::set_size(Size s) {
    Widget::set_size(s);
    refresh_image();
}
bool Image::load(const std::string &p) {
    if (!impl_->data.load(p))
        return false;
    refresh_image();
    return true;
}
void Image::set_image(const ImageData &d) {
    impl_->data = d;
    refresh_image();
}
void Image::set_fit(ImageFit f) {
    impl_->fit = f;
    refresh_image();
}
void Image::refresh_image() {
    detail::backend::ImagePixels p;
    if (!impl_->data.empty()) {
        p.width = impl_->data.width();
        p.height = impl_->data.height();
        p.channels = impl_->data.channels();
        p.pixels.assign(impl_->data.data(),
                        impl_->data.data() +
                            size_t(p.width) * p.height * p.channels);
    }
    detail::backend::image_set(native_handle(),
                               impl_->data.empty() ? nullptr : &p, impl_->fit,
                               size().width, size().height);
}
Spacer::Spacer(Size s) : Widget(nullptr) { set_size(s); }
} // namespace front
