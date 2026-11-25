#pragma once
#include <backend/Game.hpp>
#include <front/front.hpp>
#include <frontend/screen_manager.hpp>
#include <cstddef>
#include <memory>
#include <functional>

class App {
public:
    App();
    void run();
    void post(std::function<void()> callback);
    void show_menu();
    void show_rules();
    void show_player_count();
    void start_game(std::size_t count);
    void show_game();
    void show_result();
    void next_round();
    void place_bet(int amount);
    void hit();
    void stand();
    const backend::GameData& game_data() const noexcept { return data_; }
    int selected_bet() const noexcept { return selected_bet_; }
private:
    front::Window window_{1280, 900, "Blackjack"};
    backend::Game game_;
    backend::GameData data_;
    ScreenManager screens_{window_};
    int selected_bet_{50};
    void show_error(backend::GameError error);
};
