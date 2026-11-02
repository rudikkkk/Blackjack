#pragma once

#include <iostream>
#include <string>

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
    int value{2};

    explicit Card(Rank &r, Suit &s);

    bool is_ace() const { return rank == Rank::Ace; }
};
