#pragma once

#include "Hand.hpp"
#include "types.hpp"

namespace backend {

struct Player : Hand {
    int balance_{START_BALANCE};
    int bet_{0};
    PlayerStates state_ = PlayerStates::None;
    bool can_bet(int amount) { return balance_ >= static_cast<int>(amount); }
    bool can_hit() { return (!is_bust() && get_total() != 21); }
};

} // namespace backend
