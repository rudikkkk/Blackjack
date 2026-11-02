#include "Deck.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

Deck::Deck() : rng(std::random_device{}()) { reset(); }

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
    return;
}

void Deck::reset() {
    cards = {};

    for (int rank{2}; rank <= 14; ++rank)
        for (int suit{0}; suit < 4; ++suit)
            cards.emplace_back(static_cast<Rank>(rank),
                               static_cast<Suit>(suit));

    shuffle();
}

Card Deck::get_card() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}
