#pragma once

#include "Hand.hpp"
#include "Player.hpp"
#include "types.hpp"

#include <vector>

struct CardData {
    Rank rank{};
    Suit suit{};
    bool is_face_down{false};

    CardData(const Card &c)
        : rank{c.rank}, suit{c.suit}, is_face_down{c.is_face_down} {}
};

struct HandData {
    std::vector<CardData> cards;
    int total{0};
    bool is_blackjack{false};
    bool is_bust{false};

    HandData(const Hand &hand) {
        for (const auto card : hand.get_cards())
            cards.emplace_back(card);
    }
};

struct DealerData {
    HandData hand;

    DealerData(const Hand &d) : hand{d} {}
};

struct PlayerData {
    HandData hand; // на этапе сплита: std::vector<HandData> hands
    int balance{0};
    int bet{0};
    PlayerStates state{PlayerStates::None};

    PlayerData(const Player &p)
        : hand{p}, balance{p.balance}, bet{p.bet}, state{p.state} {}
};

struct AllowedActions {
    bool bet{false};
    bool hit{false};
    bool stand{false};
    bool next_round{false};
};

struct GameData {
    States state{States::Menu};
    std::size_t current_player{0};
    DealerData dealer;
    std::vector<PlayerData> players;

    GameData(std::size_t c_p, const Hand &d, States s,
             const std::vector<Player> &p)
        : state{s}, current_player{c_p}, dealer{d} {
        players.clear();
        for (const auto &player : p) {
            players.emplace_back(player);
        }
    }
};
