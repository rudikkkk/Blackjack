#pragma once

#include "Hand.hpp"

struct Player {
    Hand hand;
    int balance{1000};
    int bet{0};
    bool can_bet(unsigned int amount) { return balance >= amount; }
};