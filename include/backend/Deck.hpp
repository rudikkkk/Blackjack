#pragma once

#include "Card.hpp"
#include <vector>

std::random_device rd;
std::mt19937 g(rd());

class Deck {
  private:
    std::vector<Card> cards;

  public:
    Deck() { reset(); };

    void shuffle() {};

    void reset() {};

    Card get_card() {};

    Card operator[](int i) { return cards[i]; }
};
