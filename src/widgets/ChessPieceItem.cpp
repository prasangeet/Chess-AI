#include "widgets/ChessPieceItem.hpp"

#include "game/Piece.hpp"
#include "game/PieceType.hpp"
#include "game/Color.hpp"
#include <QSvgRenderer>

ChessPieceItem::ChessPieceItem(
    const Piece* piece,
    QGraphicsItem* parent
)
    : QGraphicsSvgItem(parent),
      piece_(piece)
{
    if (piece_) {
        setSharedRenderer(new QSvgRenderer(assetPath(*piece_)));
    }
}

const Piece* ChessPieceItem::piece() const
{
    return piece_;
}

QString ChessPieceItem::assetPath(const Piece& piece)
{
    const QString prefix =
        piece.color() == Color::White ? ":/w_" : ":/b_";

    switch (piece.pieceType()) {
    case PieceType::Pawn:
        return prefix + "pawn.svg";

    case PieceType::Knight:
        return prefix + "knight.svg";

    case PieceType::Bishop:
        return prefix + "bishop.svg";

    case PieceType::Rook:
        return prefix + "rook.svg";

    case PieceType::Queen:
        return prefix + "queen.svg";

    case PieceType::King:
        return prefix + "king.svg";
    }

    return {};
}
