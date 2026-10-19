#include "hand.cpp"
#include <array>

class Player {
    std::array<Hand, 2> hands{Hand(), Hand()};
    bool is_splited = false;
    int balance{0};

    void do_split() {
        hands[0].split(hands[1]);
        is_splited = true;
    }
};