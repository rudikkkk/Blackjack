#include "Hand.hpp"
#include "Card.hpp"

void Hand::add(Card &card) {
    cards.push_back(card);
    count_total();
}

void Hand::count_total() {
    int aces{0};
    int res{0};
    for (Card c : cards) {
        res += c.value();
        if (c.is_ace()) {
            ++aces;
        }
    }
    while (res > 21 && aces > 0) {
        res -= 10;
        --aces;
    }
    total = res;
}
