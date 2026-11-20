#include "Deck.hpp"
#include "Card.hpp"
#include "constants.hpp"
#include <algorithm>
#include <random>
#include <vector>

namespace backend {

Deck::Deck() : rng(std::random_device{}()) { reset(); }

void Deck::shuffle() { std::shuffle(cards.begin(), cards.end(), rng); }

void Deck::reset() {
    cards = {};
    cards.reserve(N_DECKS * CARDS_IN_DECK);
    for (int i{0}; i < N_DECKS; ++i)
        for (int rank{2}; rank <= 14; ++rank)
            for (int suit{0}; suit < 4; ++suit)
                cards.emplace_back(static_cast<Rank>(rank),
                                   static_cast<Suit>(suit));

    shuffle();
}

Card Deck::get_card() {
    if (cards.empty()) {
        reset();
    }
    Card card = std::move(cards.back());
    cards.pop_back();
    return card;
}

} // namespace backend