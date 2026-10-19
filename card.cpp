#include <iostream>
#include <string>

struct Card {
    int value{0};
    std::string name{""};
    char suit{' '};
    bool is_ace = false;

    explicit Card(const std::string &str) {
        suit = str[str.size() - 1];

        if (str.size() < 2)
            throw std::invalid_argument("bad card");
        suit = str.back();
        std::string rank = str.substr(0, str.size() - 1);
        if (rank == "A") {
            value = 11;
            name = "A";
            is_ace = true;
        } else if (rank == "K") {
            value = 10;
            name = "K";
        } else if (rank == "Q") {
            value = 10;
            name = "Q";
        } else if (rank == "J") {
            value = 10;
            name = "J";
        } else if (rank == "10") {
            value = 10;
            name = "10";
        } else if (rank.size() == 1 && rank[0] >= '2' && rank[0] <= '9') {
            value = rank[0] - '0';
            name = rank;
        } else
            throw std::invalid_argument("bad rank: " + rank);
    }
};

std::ostream &operator<<(std::ostream &os, const Card &c) {
    os << c.name << c.suit;
    return os;
}