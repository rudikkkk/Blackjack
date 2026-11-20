#pragma once

#include "Hand.hpp"
#include "Player.hpp"
#include "types.hpp"

#include <vector>

namespace backend {

struct CardData {
    Rank rank_{};
    Suit suit_{};
    bool is_face_down_{false};

    CardData(const Card &c)
        : rank_{c.rank_}, suit_{c.suit_}, is_face_down_{c.is_face_down_} {}
};

struct HandData {
    std::vector<CardData> cards_;
    int total_{0};
    bool is_blackjack_{false};
    bool is_bust{false};

    HandData(const Hand &hand) {
        for (const auto card : hand.get_cards())
            cards_.emplace_back(card);
        total_ = hand.get_total();
        is_blackjack_ = hand.is_blackjack();
        is_bust = hand.is_bust();
    }
};

struct DealerData {
    HandData hand_;

    DealerData(const Hand &d) : hand_{d} {}
};

struct PlayerData {
    HandData hand_; // при добавлении сплита: std::vector<HandData> hands
    int balance_{0};
    int bet_{0};
    PlayerStates state{PlayerStates::None};

    PlayerData(const Player &p)
        : hand_{p}, balance_{p.balance_}, bet_{p.bet_}, state{p.state_} {}
};

// На будущее
// struct AllowedActions {
//     bool bet{false};
//     bool hit{false};
//     bool stand{false};
//     bool next_round{false};
// };

struct GameData {
    States state_{States::Menu};
    std::size_t current_player_{0};
    DealerData dealer_;
    std::vector<PlayerData> players_;
    GameError error_{GameError::None};

    GameData(std::size_t c_p, const Hand &d, States s,
             const std::vector<Player> &players)
        : state_{s}, current_player_{c_p}, dealer_{d} {
        players_.clear();
        for (const auto &p : players) {
            players_.emplace_back(p);
        }
    }
};

} // namespace backend
