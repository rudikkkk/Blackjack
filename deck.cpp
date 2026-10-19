#include "card.cpp"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

class Deck {
    std::vector<Card> deck;

  public:
    explicit Deck() { reset(); }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
        return;
    }

    void reset() {
        deck = {};
        const char *ranks[] = {"2", "3",  "4", "5", "6", "7", "8",
                               "9", "10", "J", "Q", "K", "A"};
        for (auto r : ranks)
            for (char c : {'h', 'c', 'd', 's'})
                deck.emplace_back(std::string(r) + c);
    }

    Card get_card() {
        Card card = deck.back();
        deck.pop_back();
        return card;
    }

    Card operator[](int i) { return deck[i]; }
};
