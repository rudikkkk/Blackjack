#pragma once
#include <FL/Fl_Group.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

namespace front::detail {

inline Fl_Widget *widget(void *p) noexcept {
    return static_cast<Fl_Widget *>(p);
}

inline Fl_Group *group(void *p) noexcept { return static_cast<Fl_Group *>(p); }

inline Fl_Window *window(void *p) noexcept {
    return static_cast<Fl_Window *>(p);
}
} // namespace front::detail
