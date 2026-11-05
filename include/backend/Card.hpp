#pragma once

#include <algorithm>

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
    Rank rank{Rank::Two};
    Suit suit{Suit::Clubs};

    Card(Rank r, Suit s) : rank{r}, suit{s} {}

    bool is_ace() const { return rank == Rank::Ace; }

    int value() const { is_ace() ? 11 : std::min(10, static_cast<int>(rank)); }
};
