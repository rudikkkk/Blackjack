#include <frontend/screens/player_count_screen.hpp>
#include <frontend/app.hpp>
#include <string>
void PlayerCountScreen::render(front::Group& root) {
    label(root, "ВЫБОР ИГРОКОВ", 300, 150, 500, 60, 32).set_text_color(front::colors::blue);
    label(root, "Сколько игроков будет за столом?", 300, 245, 500, 45, 21);
    for (std::size_t count = 1; count <= 4; ++count) {
        const int x = 190 + static_cast<int>(count - 1) * 185;
        button(root, std::to_string(count), x, 340, 135, 90,
               [this, count] { app_.start_game(count); });
    }
    button(root, "Назад", 400, 520, 300, 58, [this] { app_.show_menu(); });
}
