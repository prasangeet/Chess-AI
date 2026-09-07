#pragma once

#include "game/Piece.hpp"

#include <vector>

class Board;
class Position;

class Bishop final : public Piece
{
public:
    explicit Bishop(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
