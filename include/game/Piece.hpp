#pragma once

#include "game/Color.hpp"
#include "game/PieceType.hpp"
#include "game/Position.hpp"

#include <vector>

class Board;

class Piece
{
public:
    Piece(Color color, PieceType pieceType);
    virtual ~Piece();

    Color color() const;
    PieceType pieceType() const;

    virtual std::vector<Position> validMoves(
        const Board& board,
        const Position& from
    ) const = 0;

private:
    Color color_;
    PieceType pieceType_;
};
