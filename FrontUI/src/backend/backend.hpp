#pragma once
#include <cstdint>
#include <front/core/types.hpp>
#include <functional>
#include <string>
#include <vector>

namespace front {
enum class ImageFit;
}
namespace front::detail::backend {
using Handle = void *;
struct ImagePixels {
    int width{}, height{}, channels{3};
    std::vector<std::uint8_t> pixels;
};
Handle create_widget(int x, int y, int w, int h);
Handle create_group(int x, int y, int w, int h);
Handle create_label(int x, int y, int w, int h, const char *text);
Handle create_button(int x, int y, int w, int h, const char *text,
                     std::function<void()> callback);
Handle create_image_widget(int x, int y, int w, int h);
void destroy_widget(Handle);
void widget_geometry(Handle, int x, int y, int w, int h);
void widget_show(Handle, bool);
void widget_enable(Handle, bool);
void widget_redraw(Handle);
void group_add(Handle group, Handle child);
void group_remove(Handle group, Handle child);
void group_clear(Handle group);
void label_text(Handle, const char *);
void label_color(Handle, Color);
void label_font_size(Handle, int);
void button_text(Handle, const char *);
void button_color(Handle, Color);
void image_set(Handle, const ImagePixels *, ImageFit fit, int target_w,
               int target_h);
bool image_load(const std::string &, ImagePixels &);
Handle create_window(int w, int h, const char *title);
void window_title(Handle, const char *);
void window_size(Handle, int w, int h);
void window_resizable(Handle, bool);
void window_show(Handle, bool);
void window_redraw(Handle);
void window_attach_root(Handle window, Handle group);
void window_detach_root(Handle window, Handle group);
void window_destroy(Handle);
int run();
void timer_add(double seconds, void (*callback)(void *), void *data);
void timer_repeat(double seconds, void (*callback)(void *), void *data);
void timer_remove(void (*callback)(void *), void *data);
} // namespace front::detail::backend
