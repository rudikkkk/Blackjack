#pragma once

#include <algorithm>

namespace backend {

enum class Suit { Clubs, Diamonds, Hearts, Spades };

enum class Rank : int {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

struct Card {
    Rank rank_{Rank::Two};
    Suit suit_{Suit::Clubs};
    bool is_face_down_{false};

    Card(Rank r, Suit s) : rank_{r}, suit_{s} {}

    bool is_ace() const { return rank_ == Rank::Ace; }

    int value() const {
        return is_ace() ? 11 : std::min(10, static_cast<int>(rank_));
    }
};

} // namespace backend
