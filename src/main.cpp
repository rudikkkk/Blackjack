#include <front/front.hpp>

int main() {
    front::ResourceManager::set_resource_directory(ASSETS_DIR);
    front::Window window(640, 420, "BlackJack");
    auto &root = window.root();
    root.set_layout(std::make_unique<front::VerticalLayout>(12, 18));

    auto &title = root.create<front::Label>("Front UI", front::Size{260, 42});
    title.set_text_color(front::colors::blue);
    title.set_font_size(24);

    auto &status = root.create<front::Label>("Ready", front::Size{260, 30});
    auto &button = root.create<front::Button>("Click", front::Size{200, 40});
    button.set_on_click([&status] { status.set_text("Button clicked!"); });

    auto &logo = root.create<front::Image>(front::Size{300, 200});
    logo.set_fit(front::ImageFit::contain);
    logo.load("sample.jpeg");

    window.show();
    window.run();
}
