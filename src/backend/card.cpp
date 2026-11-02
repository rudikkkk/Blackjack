#include "Card.hpp"

Card::Card(Rank &r, Suit &s) {
    rank = r;
    suit = s;
    if (is_ace()) {
        value = 11;
    } else {
        value = std::min(10, static_cast<int>(r));
    }
}