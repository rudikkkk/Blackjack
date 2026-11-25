#include <frontend/app.hpp>
#include <frontend/screens/game_screen.hpp>
#include <frontend/screens/menu_screen.hpp>
#include <frontend/screens/player_count_screen.hpp>
#include <frontend/screens/result_screen.hpp>
#include <frontend/screens/rules_screen.hpp>

#include <algorithm>
#include <string>
#include <utility>

App::App() : data_(game_.start(1)) {
    window_.root().set_background({226, 235, 224});
    show_menu();
}

void App::run() {
    window_.show();
    window_.run();
}

void App::post(std::function<void()> callback) {
    window_.post(std::move(callback));
}

void App::show_menu() {
    screens_.show(std::make_unique<MenuScreen>(*this));
}

void App::show_rules() {
    screens_.show(std::make_unique<RulesScreen>(*this));
}

void App::show_player_count() {
    screens_.show(std::make_unique<PlayerCountScreen>(*this));
}

void App::start_game(std::size_t count) {
    data_ = game_.start(count);
    selected_bet_ = backend::MIN_BET;
    show_game();
}

void App::show_game() {
    if (data_.state_ == backend::States::End) {
        show_result();
        return;
    }
    screens_.show(std::make_unique<GameScreen>(*this));
    if (data_.error_ != backend::GameError::None)
        show_error(data_.error_);
}

void App::show_result() {
    screens_.show(std::make_unique<ResultScreen>(*this));
}

void App::next_round() {
    data_ = game_.next_round();
    selected_bet_ = backend::MIN_BET;
    show_game();
}

void App::place_bet(int amount) {
    selected_bet_ = amount;
    data_ = game_.do_bet(selected_bet_);
    if (data_.error_ != backend::GameError::None) {
        show_game();
        return;
    }
    selected_bet_ = backend::MIN_BET;
    show_game();
}

void App::hit() {
    data_ = game_.hit();
    if (data_.state_ == backend::States::PlayersTurns &&
        data_.players_[data_.current_player_].hand_.is_bust) {
        data_ = game_.hit();
    }
    if (data_.state_ == backend::States::End)
        show_result();
    else
        show_game();
}

void App::stand() {
    data_ = game_.stand();
    if (data_.state_ == backend::States::End)
        show_result();
    else
        show_game();
}

void App::show_error(backend::GameError error) {
    std::string message;
    switch (error) {
    case backend::GameError::None: return;
    case backend::GameError::WrongState: message = "Действие недоступно в текущем состоянии игры"; break;
    case backend::GameError::NoPlayers: message = "Не выбраны игроки"; break;
    case backend::GameError::NotEnoughMoney: message = "Недостаточно средств для ставки"; break;
    case backend::GameError::BetOutOfRange: message = "Минимальная ставка — " + std::to_string(backend::MIN_BET); break;
    }
    auto& error_label = window_.root().create<front::Label>(
        message, front::Size{760, 30});
    error_label.set_position({170, 775});
    error_label.set_size({760, 30});
    error_label.set_font_size(15);
    error_label.set_text_color(front::colors::red);
    window_.redraw();
}
