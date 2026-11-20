#pragma once

#include "Hand.hpp"
#include "types.hpp"

namespace backend {

struct Player : Hand {
    int balance{START_BALANCE};
    int bet{0};
    PlayerStates state = PlayerStates::None;
    bool can_bet(unsigned int amount) {
        return balance >= static_cast<int>(amount);
    }
    bool can_hit() { return (!is_bust() && !is_blackjack()); }
};

} // namespace backend
