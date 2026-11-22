#include <front/front.hpp>
#include <memory>

int main() {
    front::Window window(640, 420, "Front UI - basic example");
    auto &root = window.root();
    root.set_layout(std::make_unique<front::VerticalLayout>(12, 18));

    auto &title = root.create<front::Label>("Front UI", front::Size{260, 42});
    title.set_text_color(front::colors::blue);
    title.set_font_size(24);

    auto &status = root.create<front::Label>("Ready", front::Size{260, 30});
    auto &button = root.create<front::Button>("Click", front::Size{200, 40});
    button.set_on_click([&status] { status.set_text("Button clicked!"); });

    auto &logo = root.create<front::Image>(front::Size{300, 300});
    logo.load("assets/sample.jpeg"); // Optional image file

    window.show();
    window.run();
}
