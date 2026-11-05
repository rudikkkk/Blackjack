#pragma once

#include "Card.hpp"
#include <vector>

class Hand {
    std::vector<Card> cards{};
    int total{0};

    void count_total();

  public:
    void add(Card &card);

    const std::vector<Card> &get_cards() const { return cards; }

    int get_total() const { return total; }

    bool is_blackjack() const { return cards.size() == 2 && total == 21; }

    bool is_bust() const { return total > 21; }

    void clear() {
        cards.clear();
        total = 0;
    }
};