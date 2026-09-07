#pragma once

#include "game/Color.hpp"
#include "game/PieceType.hpp"

#include <memory>

class Piece;

class PieceFactory
{
public:
    static std::unique_ptr<Piece> createPiece(
        PieceType type,
        Color color
    );
};
