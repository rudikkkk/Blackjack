#include <frontend/screens/menu_screen.hpp>
#include <frontend/app.hpp>
void MenuScreen::render(front::Group& root) {
    label(root, "BLACKJACK", 250, 125, 600, 70, 42).set_text_color(front::colors::blue);
    label(root, "Карточная игра против дилера", 250, 215, 600, 40, 22);
    button(root, "Играть", 390, 330, 320, 72, [this] { app_.show_player_count(); });
    button(root, "Правила", 390, 425, 320, 72, [this] { app_.show_rules(); });
    label(root, "От 1 до 4 игроков за одним столом", 300, 560, 500, 35, 17);
}
