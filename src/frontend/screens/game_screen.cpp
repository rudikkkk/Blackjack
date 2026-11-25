#include <frontend/screens/game_screen.hpp>
#include <frontend/app.hpp>
#include <frontend/card_renderer.hpp>
#include <frontend/player_panel.hpp>
#include <algorithm>
#include <string>

void GameScreen::render(front::Group& root) {
    const auto& data = app_.game_data();
    label(root, "BLACKJACK TABLE", 440, 12, 400, 38, 25).set_text_color(front::colors::blue);

    auto& dealer = panel(root, 390, 58, 500, 130);
    dealer.set_background({246, 248, 242});
    label(dealer, "ДИЛЕР", 15, 6, 470, 24, 17);
    CardRenderer::render(dealer, data.dealer_.hand_, 405, 91, 470, 48, 67);
    const bool dealer_revealed = data.state_ == backend::States::End;
    label(dealer,
          dealer_revealed ? "Очки дилера: " + std::to_string(data.dealer_.hand_.total_)
                          : "Очки дилера скрыты до завершения ходов",
          15, 102, 470, 22, 13);

    const int panel_w = 590;
    const int panel_h = 190;
    const int left = 28;
    const int right = 662;
    const int top = 195;
    const int bottom = 410;
    for (std::size_t i = 0; i < data.players_.size(); ++i) {
        int x = (i % 2 == 0) ? left : right;
        int y = (i < 2) ? top : bottom;
        if (data.players_.size() == 1) {
            x = 345; y = 300;
        } else if (data.players_.size() == 2) {
            x = i == 0 ? 28 : 662; y = 300;
        } else if (data.players_.size() == 3 && i == 2) {
            x = 345; y = bottom;
        }
        const bool active = i == data.current_player_ &&
            (data.state_ == backend::States::Betting ||
             data.state_ == backend::States::PlayersTurns);
        PlayerPanel::render(root, data.players_[i], i, active, x, y, panel_w, panel_h);
    }

    if (data.state_ == backend::States::Betting && data.current_player_ < data.players_.size()) {
        const auto& player = data.players_[data.current_player_];
        label(root, "Игрок " + std::to_string(data.current_player_ + 1) +
                    " — укажите ставку", 260, 650, 760, 30, 19);
        label(root, "Доступно: " + std::to_string(player.balance_) +
                    "     Минимум: " + std::to_string(backend::MIN_BET),
              340, 683, 600, 25, 15);
        auto& amount = root.create<front::NumberInput>(front::Size{150, 42});
        amount.set_position({440, 718});
        amount.set_size({150, 42});
        amount.set_value(std::to_string(app_.selected_bet()));
        button(root, "Подтвердить ставку", 610, 718, 230, 44, [this, &amount] {
            try { app_.place_bet(std::stoi(amount.value())); }
            catch (...) { app_.place_bet(0); }
        });
    } else if (data.state_ == backend::States::PlayersTurns) {
        label(root, "Ход игрока " + std::to_string(data.current_player_ + 1),
              360, 675, 560, 30, 19);
        button(root, "Взять карту", 365, 720, 210, 52, [this] { app_.hit(); });
        button(root, "Остановиться", 605, 720, 230, 52, [this] { app_.stand(); });
    } else if (data.state_ == backend::States::DealerTurn) {
        label(root, "Ход дилера...", 440, 710, 400, 35, 19);
    }
}
