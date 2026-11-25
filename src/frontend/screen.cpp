#include <frontend/screen.hpp>
#include <frontend/app.hpp>

front::Label& Screen::label(front::Group& parent, std::string text,
                            int x, int y, int w, int h, int font) {
    auto& item = parent.create<front::Label>(std::move(text), front::Size{w, h});
    const auto origin = parent.position();
    item.set_position({origin.x + x, origin.y + y});
    item.set_size({w, h});
    item.set_font_size(font);
    return item;
}

front::Button& Screen::button(front::Group& parent, std::string text,
                              int x, int y, int w, int h,
                              std::function<void()> callback) {
    auto& item = parent.create<front::Button>(std::move(text), front::Size{w, h});
    const auto origin = parent.position();
    item.set_position({origin.x + x, origin.y + y});
    item.set_size({w, h});
    item.set_on_click([this, callback = std::move(callback)]() mutable {
        // Не уничтожаем экран прямо внутри FLTK callback.
        app_.post(std::move(callback));
    });
    return item;
}

front::Group& Screen::panel(front::Group& parent, int x, int y, int w, int h) {
    auto& item = parent.create<front::Group>(front::Size{w, h});
    const auto origin = parent.position();
    item.set_position({origin.x + x, origin.y + y});
    item.set_size({w, h});
    return item;
}
