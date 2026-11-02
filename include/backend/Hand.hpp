#pragma once

#include "Card.hpp"
#include <vector>

class Hand {
    std::vector<Card> cards{};

    void count_total() {}

  public:
    int total{0};

    void add(Card card) {}

    const std::vector<Card> &get_cards() const { return cards; }

    bool is_blackjack() { return cards.size() == 2 && total == 21; }

    bool is_bust() { return total > 21; }
};