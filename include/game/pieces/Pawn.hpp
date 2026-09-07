#pragma once

#include "game/Piece.hpp"

class Board;
class Position;

class Pawn final : public Piece
{
public:
    explicit Pawn(Color color);

    std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const override;
};
