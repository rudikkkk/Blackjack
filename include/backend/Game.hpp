#pragma once

#include "Deck.hpp"
#include "Player.hpp"
#include <cstddef>
#include <vector>

class Game {
    Deck deck{};
    std::vector<Player> players{};

  public:
    void start(std::size_t player_count);
    void to_menu();
    void next_round();
    bool do_bet(std::size_t player_id, unsigned int amount);

    void hit();
    void stand();

    void next_step();
};
