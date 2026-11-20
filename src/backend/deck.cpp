#include "Deck.hpp"
#include "Card.hpp"
#include "constants.hpp"
#include <algorithm>
#include <random>
#include <vector>

namespace backend {

Deck::Deck() : rng_(std::random_device{}()) { reset(); }

void Deck::shuffle() { std::shuffle(cards_.begin(), cards_.end(), rng_); }

void Deck::reset() {
    cards_ = {};
    cards_.reserve(N_DECKS * CARDS_IN_DECK);
    for (int i{0}; i < N_DECKS; ++i)
        for (int rank{2}; rank <= 14; ++rank)
            for (int suit{0}; suit < 4; ++suit)
                cards_.emplace_back(static_cast<Rank>(rank),
                                    static_cast<Suit>(suit));

    shuffle();
}

Card Deck::get_card() {
    if (cards_.empty()) {
        reset();
    }
    Card card = std::move(cards_.back());
    cards_.pop_back();
    return card;
}

} // namespace backend