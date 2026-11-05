#pragma once

#include "Card.hpp"
#include <random>
#include <vector>

constexpr int n_decks = 2;

class Deck {
    std::mt19937 rng;
    std::vector<Card> cards;

  public:
    void shuffle();

    void reset();

    Card get_card();
};
