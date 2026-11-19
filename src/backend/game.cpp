#include "Game.hpp"
#include "Deck.hpp"
#include "GameData.hpp"

#include <algorithm>

GameData Game::get_game_data() {
    return GameData{current_player, dealer, state, players};
}

GameData Game::start(std::size_t player_count) {
    state = States::Betting;
    current_player = 0;
    dealer.clear();
    deck.reset();
    players.clear();
    players.reserve(player_count);
    players.assign(player_count, Player{});
    return get_game_data();
}

void Game::deal_the_cards() {
    dealer.add(deck.get_card());
    Card card = deck.get_card();
    card.is_face_down = true;
    dealer.add(card);
    for (auto &player : players) {
        for (int i{0}; i < 2; ++i) {
            player.add(deck.get_card());
        }
    }
}

GameData Game::next_step() {
    switch (state) {
    case States::Betting:
        if (current_player < players.size() - 1) {
            ++current_player;
        } else {
            current_player = 0;
            state = States::PlayersTurns;
            deal_the_cards();
        }
        return get_game_data();
    case States::PlayersTurns:
        if (current_player < players.size() - 1) {
            ++current_player;
            return get_game_data();
        } else {
            current_player = 0;
            state = States::DealerTurn;
            return dealer_turn();
        }
    case States::DealerTurn:
        state = States::End;
        count_results();
        return get_game_data();
    default:
        return get_game_data();
    }
}

GameData Game::do_bet(unsigned int amount) {
    Player &player = players[current_player];
    if (player.can_bet(amount)) {
        player.bet = amount;
        player.balance -= amount;
        return next_step();
    }
    return get_game_data();
}

GameData Game::hit() {
    if (state == States::PlayersTurns) {
        Player &player = players[current_player];
        if (player.can_hit()) {
            Card card = deck.get_card();
            player.add(card);
            if (!player.can_hit()) {
                player.state = PlayerStates::Lose;
                return next_step();
            }
        }
    }
    return get_game_data();
}

GameData Game::stand() {
    if (state == States::PlayersTurns) {
        return next_step();
    }
    return get_game_data();
}

GameData Game::dealer_turn() {
    auto cards = dealer.get_cards();
    cards[1].is_face_down = false;
    dealer.clear();
    dealer.add(cards[0]);
    dealer.add(cards[1]);

    bool all_players_bust = true;
    int max_player_total = 0;
    for (auto player : players) {
        if (!player.is_bust()) {
            all_players_bust = false;
            max_player_total = std::max(max_player_total, player.get_total());
        }
    }

    while (!all_players_bust && dealer.get_total() < 17 &&
           dealer.get_total() < max_player_total) {
        Card card = deck.get_card();
        dealer.add(card);
    }
    return next_step();
}

void Game::count_results() {
    for (auto &player : players) {
        if (!player.is_bust()) {
            if (player.get_total() > dealer.get_total()) {
                player.state = PlayerStates::Win;

            } else if (player.get_total() == dealer.get_total()) {
                if (player.is_blackjack() && !dealer.is_blackjack()) {
                    player.state = PlayerStates::Blackjack;
                } else if (!player.is_blackjack() && dealer.is_blackjack()) {
                    player.state = PlayerStates::Lose;
                } else {
                    player.state = PlayerStates::Draw;
                }

            } else {
                player.state = PlayerStates::Lose;
            }
        } else {
            player.state = PlayerStates::Lose;
        }

        switch (player.state) {
        case PlayerStates::Blackjack:
            player.balance += static_cast<int>(2.5 * player.bet);
            break;
        case PlayerStates::Win:
            player.balance += 2 * player.bet;
            break;
        case PlayerStates::Draw:
            player.balance += player.bet;
            break;
        default:
            break;
        }
        player.bet = 0;
    }
}
