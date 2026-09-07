#pragma once

#include "game/Piece.hpp"

#include <vector>

class Board;
class Position;

class King final : public Piece
{
public:
    explicit King(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
