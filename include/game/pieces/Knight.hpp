#pragma once

#include "game/Piece.hpp"

#include <vector>

class Board;
class Position;

class Knight final : public Piece
{
public:
    explicit Knight(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
