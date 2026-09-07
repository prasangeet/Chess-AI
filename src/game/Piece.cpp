#include "game/Piece.hpp"

Piece::Piece(Color color, PieceType type)
    : color_(color),
      pieceType_(type)
{
}

Piece::~Piece() = default;

Color Piece::color() const
{
    return color_;
}

PieceType Piece::pieceType() const
{
    return pieceType_;
}
