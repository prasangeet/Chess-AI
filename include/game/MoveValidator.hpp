#pragma once

#include "game/Move.hpp"
#include "game/Position.hpp"
#include <vector>
class Game;

class MoveValidator{
public:
    static std::vector<Move> legalMoves(
        const Game& game,
        Position from
    );

    static bool isLegalMove(
        const Game& game,
        const Move& move
    );
};