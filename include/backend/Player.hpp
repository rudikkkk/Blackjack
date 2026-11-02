#include "Card.hpp"
#include "Hand.hpp"
#include <vector>

struct Player {
    Hand hand;
    int balance{0};
    int bet{0};
    bool can_bet(const int &amount) { return balance >= amount; }
};