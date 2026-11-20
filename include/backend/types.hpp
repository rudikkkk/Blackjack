#pragma once

namespace backend {

enum class States { Menu, Betting, PlayersTurns, DealerTurn, End };
enum class PlayerStates { None = -1, Lose, Draw, Win, Blackjack };
enum class GameError {
    None = 0,
    WrongState,
    NoPlayers,
    NotEnoughMoney,
    BetOutOfRange
};

} // namespace backend
