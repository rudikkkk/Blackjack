#include <vector>

class Hand {

  public:
    std::vector<Card> cards{};
    bool is_blackjack = false;
    int sum_of_cards{0};
    explicit Hand() = default;
    explicit Hand(Card c) { cards = {c}; }
    explicit Hand(std::vector<Card> c) { cards = c; }

    void add_card(Card card) {
        cards.push_back(card);
        sum();
    }

    void split(Hand &h2) {
        h2.add_card(cards[1]);
        remove_last_card();
    }

  private:
    void remove_last_card() { cards.pop_back(); }

    void sum() {
        int aces{0};
        int res{0};
        for (Card c : cards) {
            if (c.is_ace) {
                ++aces;
            }
            res += c.value;
        }
        while (res > 21 && aces > 0) {
            res -= 10;
            --aces;
        }
        is_blackjack = (cards.size() == 2 && res == 21);
        sum_of_cards = res;
    }
};
