#pragma once

#include <iostream>
#include <string>

struct Card {
    int value{0};
    std::string name{""};
    char suit{' '};
    bool is_ace = false;

    explicit Card(const std::string &str);
};

std::ostream &operator<<(std::ostream &os, const Card &c);
