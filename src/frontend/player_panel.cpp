#include <frontend/player_panel.hpp>
#include <frontend/card_renderer.hpp>
#include <string>

namespace {
std::string state_name(backend::PlayerStates state) {
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

void PlayerPanel::render(front::Group& parent, const backend::PlayerData& player,
                         std::size_t index, bool active, int x, int y,
                         int width, int height) {
    auto& panel = parent.create<front::Group>(front::Size{width, height});
    panel.set_position({x, y});
    panel.set_size({width, height});
    panel.set_background({246, 248, 242});

    auto add = [&](std::string text, int local_y, int h, int font) -> front::Label& {
        auto& label = panel.create<front::Label>(std::move(text), front::Size{width - 24, h});
        label.set_position({x + 12, y + local_y});
        label.set_size({width - 24, h});
        label.set_font_size(font);
        return label;
    };

    auto& title = add("ИГРОК " + std::to_string(index + 1) +
                      (active ? "  • ВАШ ХОД" : ""), 8, 28, 18);
    title.set_text_color(active ? front::colors::blue : front::colors::black);
    add("Баланс: " + std::to_string(player.balance_) +
        "      Ставка: " + std::to_string(player.bet_), 39, 24, 14);
    CardRenderer::render(panel, player.hand_, x + 12, y + 68, width - 24, 48, 68);
    add("Очки: " + std::to_string(player.hand_.total_) + "      " + state_name(player.state),
        height - 31, 23, 14);
}
