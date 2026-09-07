#include "game/PieceFactory.hpp"

#include "game/Piece.hpp"
#include "game/pieces/Bishop.hpp"
#include "game/pieces/King.hpp"
#include "game/pieces/Knight.hpp"
#include "game/pieces/Pawn.hpp"
#include "game/pieces/Queen.hpp"
#include "game/pieces/Rook.hpp"

std::unique_ptr<Piece> PieceFactory::createPiece(
    PieceType type,
    Color color
)
{
    switch (type) {
    case PieceType::Pawn:
        return std::make_unique<Pawn>(color);

    case PieceType::Knight:
        return std::make_unique<Knight>(color);

    case PieceType::Bishop:
        return std::make_unique<Bishop>(color);

    case PieceType::Rook:
        return std::make_unique<Rook>(color);

    case PieceType::Queen:
        return std::make_unique<Queen>(color);

    case PieceType::King:
        return std::make_unique<King>(color);
    }

    return nullptr;
}
