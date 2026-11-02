#include "deck.cpp"
#include "hand.cpp"
#include <iostream>

int main() {
    Deck deck;
    deck.shuffle();

    Hand h{deck.get_card()};
    h.add_card(deck.get_card());

    std::cout << h.cards[0] << " " << h.cards[1] << std::endl;
    std::cout << "Sum of cards: " << h.sum_of_cards << std::endl;
    if (h.is_blackjack) {
        std::cout << "Blackjack!" << std::endl;
    }
    while (h.sum_of_cards < 21) {
        std::cout << "Want to take another card?" << std::endl;
        char ans{' '};
        std::cin >> ans;
        if (ans == 'y') {
            h.add_card(deck.get_card());
            for (Card c : h.cards) {
                std::cout << c << ' ';
            }
            std::cout << std::endl;
            std::cout << "Sum of cards: " << h.sum_of_cards << std::endl;
        } else {
            break;
        }
    }
    if (h.sum_of_cards > 21) {
        std::cout << "Bust!";
    }
    return 0;
}