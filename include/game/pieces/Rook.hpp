#pragma once

#include "game/Piece.hpp"

#include <vector>

class Board;
class Position;

class Rook final : public Piece
{
public:
    explicit Rook(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
