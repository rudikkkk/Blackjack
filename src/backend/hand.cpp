#include "Hand.hpp"
#include "Card.hpp"

namespace backend {

void Hand::add(const Card &card) {
    cards.push_back(card);
    count_total();
}

void Hand::count_total() {
    int aces{0};
    int res{0};
    for (const Card &c : cards) {
        if (!c.is_face_down) {
            res += c.value();
            if (c.is_ace()) {
                ++aces;
            }
        }
    }
    while (res > TOTAL_FOR_BLACKJACK && aces > 0) {
        res -= 10;
        --aces;
    }
    total = res;
}

} // namespace backend
