#include "Deck.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), g);
    return;
}

void Deck::reset() {
    cards = {};
    const char *ranks[] = {"2", "3",  "4", "5", "6", "7", "8",
                           "9", "10", "J", "Q", "K", "A"};
    for (auto r : ranks)
        for (char c : {'h', 'c', 'd', 's'})
            cards.emplace_back(std::string(r) + c);
}

Card Deck::get_card() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}
