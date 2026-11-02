#include "hand.cpp"
#include <array>

class Player {
    std::array<Hand, 2> hands{Hand(), Hand()};
    int balance{0};

    void can_split() {
        if (hands[1].sum_of_cards() == 0){
            
        }
    }

    void do_split() {
        hands[0].split(hands[1]);

    }
};