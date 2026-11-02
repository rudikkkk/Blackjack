#pragma once

#include "Card.hpp"
#include <random>
#include <vector>

class Deck {
    std::mt19937 rng;
    std::vector<Card> cards;

    void shuffle() {};

  public:
    Deck();

    void reset() {};

    Card get_card() {};
};
