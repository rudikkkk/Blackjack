#include "Game.hpp"
#include "Deck.hpp"
#include "GameData.hpp"

#include <algorithm>

namespace backend {

GameData Game::get_game_data() {
    return GameData{current_player_, dealer_, state_, players_};
}

GameData Game::start(std::size_t player_count) {
    if (player_count == 0) {
        return error(GameError::NoPlayers);
    }
    dealer_.clear();
    deck_.reset();
    players_.clear();
    players_.assign(player_count, Player{});
    current_player_ = 0;
    state_ = States::Betting;
    return get_game_data();
}

void Game::deal_the_cards() {
    dealer_.add(deck_.get_card());
    Card card = deck_.get_card();
    card.is_face_down_ = true;
    dealer_.add(card);
    for (auto &player : players_) {
        for (int i{0}; i < 2; ++i) {
            player.add(deck_.get_card());
        }
    }
}

GameData Game::next_step() {
    switch (state_) {
    case States::Betting:
        if (current_player_ < players_.size() - 1) {
            ++current_player_;
        } else {
            current_player_ = 0;
            state_ = States::PlayersTurns;
            deal_the_cards();
        }
        return get_game_data();
    case States::PlayersTurns:
        if (current_player_ < players_.size() - 1) {
            ++current_player_;
            return get_game_data();
        } else {
            current_player_ = 0;
            state_ = States::DealerTurn;
            return dealer_turn();
        }
    case States::DealerTurn:
        state_ = States::End;
        count_results();
        return get_game_data();
    default:
        return get_game_data();
    }
}

GameData Game::do_bet(int amount) {
    if (state_ != States::Betting) {
        return error(GameError::WrongState);
    }
    Player &player = players_[current_player_];

    if (amount < MIN_BET) {
        return error(GameError::BetOutOfRange);
    }

    if (!player.can_bet(amount)) {
        return error(GameError::NotEnoughMoney);
    }
    player.bet_ = amount;
    player.balance_ -= amount;
    return next_step();
}

GameData Game::hit() {
    if (state_ != States::PlayersTurns) {
        return error(GameError::WrongState);
    }
    Player &player = players_[current_player_];
    if (player.can_hit()) {
        Card card = deck_.get_card();
        player.add(card);
    }
    if (!player.can_hit()) {
        if (player.is_blackjack()) {
            player.state_ = PlayerStates::Blackjack;
        } else if (player.get_total() != 21) {
            player.state_ = PlayerStates::Lose;
        }
        return next_step();
    }
    return get_game_data();
}

GameData Game::stand() {
    if (state_ != States::PlayersTurns) {
        return error(GameError::WrongState);
    }
    return next_step();
}

GameData Game::dealer_turn() {
    auto cards = dealer_.get_cards();
    cards[1].is_face_down_ = false;
    dealer_.clear();
    dealer_.add(cards[0]);
    dealer_.add(cards[1]);

    bool all_players_bust = true;
    int max_player_total = 0;
    for (auto player : players_) {
        if (!player.is_bust()) {
            all_players_bust = false;
            max_player_total = std::max(max_player_total, player.get_total());
        }
    }

    while (!all_players_bust && dealer_.get_total() < DEALER_STAND_TOTAL &&
           dealer_.get_total() < max_player_total) {
        Card card = deck_.get_card();
        dealer_.add(card);
    }
    return next_step();
}

void Game::count_results() {
    for (auto &p : players_) {
        switch (p.state_) {
        case PlayerStates::Blackjack:
            p.state_ = dealer_.is_blackjack() ? PlayerStates::Draw
                                              : PlayerStates::Blackjack;
            break;

        case PlayerStates::None:
            if (dealer_.is_blackjack()) {
                p.state_ = PlayerStates::Lose;
            } else if (dealer_.is_bust() ||
                       dealer_.get_total() < p.get_total()) {
                p.state_ = PlayerStates::Win;
            } else if (p.get_total() == dealer_.get_total()) {
                p.state_ = PlayerStates::Draw;
            } else {
                p.state_ = PlayerStates::Lose;
            }
            break;

        default:
            break;
        }

        switch (p.state_) {
        case PlayerStates::Blackjack:
            p.balance_ += static_cast<int>(2.5 * p.bet_);
            break;
        case PlayerStates::Win:
            p.balance_ += 2 * p.bet_;
            break;
        case PlayerStates::Draw:
            p.balance_ += p.bet_;
            break;
        default:
            break;
        }
    }
}

GameData Game::next_round() {
    if (state_ != States::End) {
        return error(GameError::WrongState);
    }
    dealer_.clear();
    for (auto &p : players_) {
        p.clear();
        p.bet_ = 0;
        p.state_ = PlayerStates::None;
    }
    current_player_ = 0;
    state_ = States::Betting;
    return get_game_data();
}

} // namespace backend
