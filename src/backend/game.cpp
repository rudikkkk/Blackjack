#include "Game.hpp"
#include "Deck.hpp"

void Game::start(std::size_t player_count) {
    deck.reset();
    players.clear();
    players.reserve(player_count);
    for (std::size_t i{0}; i < player_count; ++i) {
        players.assign(player_count, Player{});
    }
}

bool Game::do_bet(std::size_t player_id, unsigned int amount) {
    if (player_id >= players.size())
        return false;
    auto &player = players[player_id];
    if (!player.can_bet(amount))
        return false;
    player.bet = amount;
    player.balance -= amount;
    return true;
}
