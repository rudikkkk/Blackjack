#include "Card.hpp"

Card::Card(const std::string &str) {
    if (str.size() < 2)
        throw std::invalid_argument("bad card");
    suit = str.back();
    std::string rank = str.substr(0, str.size() - 1);
    if (rank == "A") {
        value = 11;
        name = rank;
        is_ace = true;
    } else if (rank == "K" || rank == "Q" || rank == "J" || rank == "10") {
        value = 10;
        name = rank;
    } else if (rank.size() == 1 && rank[0] >= '2' && rank[0] <= '9') {
        value = rank[0] - '0';
        name = rank;
    } else
        throw std::invalid_argument("bad rank: " + rank);
}

std::ostream &operator<<(std::ostream &os, const Card &c) {
    os << c.name << c.suit;
    return os;
}