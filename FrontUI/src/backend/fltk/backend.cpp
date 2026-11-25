#include "../backend.hpp"
#include <FL/Fl.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <filesystem>
#include <front/widget/controls.hpp>
#include <memory>

namespace front::detail::backend {
namespace {
Fl_Widget *W(Handle h) { return static_cast<Fl_Widget *>(h); }
Fl_Group *G(Handle h) { return static_cast<Fl_Group *>(h); }
Fl_Window *Win(Handle h) { return static_cast<Fl_Window *>(h); }
Fl_Color to_fl(Color c) { return fl_rgb_color(c.r, c.g, c.b); }
class CallbackButton : public Fl_Button {
  public:
    CallbackButton(int x, int y, int w, int h, const char *t,
                   std::function<void()> fn)
        : Fl_Button(x, y, w, h), callback_(std::move(fn)) {
        copy_label(t);
    }

    void invoke() {
        if (callback_)
            callback_();
    }

  private:
    std::function<void()> callback_;
};
class OwnedImageBox : public Fl_Box {
  public:
    using Fl_Box::Fl_Box;
    void set_pixels(const ImagePixels *p, ImageFit fit, int tw, int th) {
        image_owner_.reset();
        pixels_.clear();
        image(nullptr);
        if (!p || p->pixels.empty()) {
            redraw();
            return;
        }
        pixels_ = p->pixels;
        auto im = std::make_unique<Fl_RGB_Image>(pixels_.data(), p->width,
                                                 p->height, p->channels);
        if (fit == ImageFit::contain) {
            float sc = std::min(float(std::max(1, tw)) / p->width,
                                float(std::max(1, th)) / p->height);
            im->scale(std::max(1, int(p->width * sc)),
                      std::max(1, int(p->height * sc)), 0, 1);
        } else if (fit == ImageFit::stretch)
            im->scale(std::max(1, tw), std::max(1, th), 0, 1);
        image_owner_ = std::move(im);
        image(image_owner_.get());
        redraw();
    }

  private:
    std::vector<unsigned char> pixels_;
    std::unique_ptr<Fl_RGB_Image> image_owner_;
};
} // namespace
Handle create_widget(int x, int y, int w, int h) {
    return new Fl_Box(x, y, w, h);
}
Handle create_group(int x, int y, int w, int h) {
    auto *g = new Fl_Group(x, y, w, h);
    g->box(FL_NO_BOX);
    return g;
}
Handle create_label(int x, int y, int w, int h, const char *t) {
    auto *b = new Fl_Box(x, y, w, h);
    b->copy_label(t);
    return b;
}
Handle create_button(int x, int y, int w, int h, const char *t,
                     std::function<void()> cb) {
    auto *b = new CallbackButton(x, y, w, h, t, std::move(cb));
    b->callback([](Fl_Widget *w,
                   void *) { static_cast<CallbackButton *>(w)->invoke(); },
                nullptr);
    return b;
}
Handle create_image_widget(int x, int y, int w, int h) {
    auto *b = new OwnedImageBox(x, y, w, h);
    b->box(FL_NO_BOX);
    return b;
}
void destroy_widget(Handle h) { delete W(h); }
void widget_geometry(Handle h, int x, int y, int w, int he) {
    if (h)
        W(h)->resize(x, y, w, he);
}
void widget_show(Handle h, bool v) {
    if (h) {
        if (v)
            W(h)->show();
        else
            W(h)->hide();
    }
}
void widget_enable(Handle h, bool v) {
    if (h) {
        if (v)
            W(h)->activate();
        else
            W(h)->deactivate();
    }
}
void widget_redraw(Handle h) {
    if (h)
        W(h)->redraw();
}
void group_add(Handle g, Handle c) {
    if (g && c)
        G(g)->add(W(c));
}
void group_remove(Handle g, Handle c) {
    if (g && c)
        G(g)->remove(W(c));
}
void group_clear(Handle g) {
    if (g)
        G(g)->clear();
}
void label_text(Handle h, const char *t) {
    if (h)
        W(h)->label(t);
}
void label_color(Handle h, Color c) {
    if (h)
        W(h)->labelcolor(to_fl(c));
}
void label_font_size(Handle h, int s) {
    if (h)
        W(h)->labelsize(std::max(1, s));
}
void button_text(Handle h, const char *t) {
    if (h)
        W(h)->label(t);
}
void button_color(Handle h, Color c) {
    if (h)
        W(h)->color(to_fl(c));
}
void image_set(Handle h, const ImagePixels *p, ImageFit fit, int tw, int th) {
    auto *b = static_cast<OwnedImageBox *>(h);
    if (!b)
        return;
    b->set_pixels(p, fit, tw, th);
}

bool image_load(const std::string &path, ImagePixels &out) {
    std::unique_ptr<Fl_Image> im;
    auto ext = std::filesystem::path(path).extension().string();
    if (ext == ".png" || ext == ".PNG")
        im = std::make_unique<Fl_PNG_Image>(path.c_str());
    else if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG")
        im = std::make_unique<Fl_JPEG_Image>(path.c_str());
    else if (ext == ".bmp" || ext == ".BMP")
        im = std::make_unique<Fl_BMP_Image>(path.c_str());
    else
        return false;
    if (!im || im->w() <= 0 || im->h() <= 0 || !im->data())
        return false;
    out.width = im->w();
    out.height = im->h();
    out.channels = 3;
    out.pixels.resize(size_t(out.width) * out.height * 3);
    const char *src = im->data()[0];
    int d = im->d();
    for (int i = 0; i < out.width * out.height; ++i) {
        out.pixels[i * 3] = src[i * d];
        out.pixels[i * 3 + 1] = d > 1 ? src[i * d + 1] : src[i * d];
        out.pixels[i * 3 + 2] = d > 2 ? src[i * d + 2] : src[i * d];
    }
    return true;
}
Handle create_window(int w, int h, const char *t) {
    return new Fl_Window(w, h, t);
}
void window_title(Handle h, const char *t) {
    if (h)
        Win(h)->label(t);
}
void window_size(Handle h, int w, int he) {
    if (h)
        Win(h)->resize(Win(h)->x(), Win(h)->y(), w, he);
}
void window_resizable(Handle h, bool v) {
    if (h)
        Win(h)->resizable(v ? Win(h) : nullptr);
}
void window_show(Handle h, bool v) {
    if (h) {
        if (v)
            Win(h)->show();
        else
            Win(h)->hide();
    }
}
void window_redraw(Handle h) {
    if (h)
        Win(h)->redraw();
}
void window_attach_root(Handle w, Handle g) {
    if (w && g) {
        Win(w)->begin();
        Win(w)->add(G(g));
        Win(w)->end();
    }
}
void window_detach_root(Handle w, Handle g) {
    if (w && g)
        Win(w)->remove(G(g));
}
void window_destroy(Handle h) { delete Win(h); }
int run() { return Fl::run(); }
void timer_add(double s, void (*cb)(void *), void *d) {
    Fl::add_timeout(s, cb, d);
}
void timer_repeat(double s, void (*cb)(void *), void *d) {
    Fl::repeat_timeout(s, cb, d);
}
void timer_remove(void (*cb)(void *), void *d) { Fl::remove_timeout(cb, d); }
} // namespace front::detail::backend
