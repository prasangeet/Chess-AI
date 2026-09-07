#pragma once

#include "game/Piece.hpp"

#include <vector>

class Board;
class Position;

class Queen final : public Piece
{
public:
    explicit Queen(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
