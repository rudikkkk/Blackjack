#include <frontend/screens/result_screen.hpp>
#include <frontend/app.hpp>
#include <frontend/player_panel.hpp>
#include <string>
namespace {
std::string result_name(backend::PlayerStates state) {
    switch (state) {
    case backend::PlayerStates::None: return "В игре";
    case backend::PlayerStates::Lose: return "Проигрыш";
    case backend::PlayerStates::Draw: return "Ничья";
    case backend::PlayerStates::Win: return "Победа";
    case backend::PlayerStates::Blackjack: return "Blackjack";
    }
    return "";
}
}
void ResultScreen::render(front::Group& root) {
    const auto& data = app_.game_data();
    label(root, "ИТОГИ РАЗДАЧИ", 330, 35, 440, 50, 30).set_text_color(front::colors::blue);
    label(root, "Дилер: " + std::to_string(data.dealer_.hand_.total_) + " очков",
          350, 105, 400, 35, 20);
    int y = 175;
    for (std::size_t i = 0; i < data.players_.size(); ++i) {
        const auto& p = data.players_[i];
        label(root, "Игрок " + std::to_string(i + 1) + " — " + result_name(p.state) +
                    " | очки: " + std::to_string(p.hand_.total_) +
                    " | баланс: " + std::to_string(p.balance_),
              130, y, 840, 42, 17);
        y += 58;
    }
    button(root, "Новая раздача", 265, 650, 240, 60, [this] {
        app_.next_round();
    });
    button(root, "В главное меню", 595, 650, 240, 60, [this] { app_.show_menu(); });
}
