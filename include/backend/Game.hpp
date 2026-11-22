#pragma once

#include "Deck.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include <cstddef>
#include <vector>

namespace backend {

class Game {
    std::size_t current_player_{0};
    Hand dealer_{};
    Deck deck_{};
    std::vector<Player> players_{};
    States state_ = States::Menu;

    GameData next_step();

    void deal_the_cards();

    GameData dealer_turn();

    void count_results();

    GameData get_game_data();

    GameData Game::error(GameError e) {
        GameData data = get_game_data();
        data.error_ = e;
        return data;
    }

  public:
    GameData start(std::size_t player_count);
    GameData next_round();

    GameData do_bet(int amount);

    GameData hit();
    GameData stand();
};

} // namespace backend
