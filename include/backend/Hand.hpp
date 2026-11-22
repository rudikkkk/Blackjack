#pragma once

#include "Card.hpp"
#include "constants.hpp"
#include <vector>

namespace backend {

class Hand {
    std::vector<Card> cards_{};
    int total_{0};

    void count_total();

  public:
    void add(const Card &card);

    const std::vector<Card> &get_cards() const { return cards_; }

    int get_total() const { return total_; }

    bool is_blackjack() const {
        return cards_.size() == 2 && total_ == TOTAL_FOR_BLACKJACK;
    }

    bool is_bust() const { return total_ > TOTAL_FOR_BLACKJACK; }

    void clear() {
        cards_.clear();
        total_ = 0;
    }
};

} // namespace backend