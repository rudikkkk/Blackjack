#pragma once

#include "Card.hpp"
#include <random>
#include <vector>

namespace backend {

class Deck {
    std::mt19937 rng_;
    std::vector<Card> cards_;

    void shuffle();

  public:
    Deck();

    void reset();

    Card get_card();
};

} // namespace backend
