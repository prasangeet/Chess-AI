#include "game/Board.hpp"

#include "game/Piece.hpp"
#include "game/Color.hpp"
#include "game/PieceFactory.hpp"
#include "game/PieceType.hpp"
#include "game/Position.hpp"

Board::Board()
{
    clear();
    setUpInitialPosition();
}

Board::~Board() = default;

Piece* Board::pieceAt(Position position)
{
    if (!position.isValid())
        return nullptr;

    return cells_[position.row()][position.col()].get();
}

const Piece* Board::pieceAt(Position position) const
{
    if (!position.isValid())
        return nullptr;

    return cells_[position.row()][position.col()].get();
}

void Board::setPiece(
    Position position,
    std::unique_ptr<Piece> piece
)
{
    if (!position.isValid())
        return;

    cells_[position.row()][position.col()] = std::move(piece);
}

std::unique_ptr<Piece> Board::removePiece(Position position)
{
    if (!position.isValid())
        return nullptr;

    auto piece = std::move(
        cells_[position.row()][position.col()]
    );

    cells_[position.row()][position.col()] = nullptr;

    return piece;
}

void Board::setUpInitialPosition()
{
    // Black back rank
    const PieceType blackBackRank[BoardSize] = {
        PieceType::Rook,
        PieceType::Knight,
        PieceType::Bishop,
        PieceType::Queen,
        PieceType::King,
        PieceType::Bishop,
        PieceType::Knight,
        PieceType::Rook
    };

    for (int column = 0; column < BoardSize; ++column) {
        setPiece(
            Position(0, column),
            PieceFactory::createPiece(
                blackBackRank[column],
                Color::Black
            )
        );
    }

    // Black pawns
    for (int column = 0; column < BoardSize; ++column) {
        setPiece(
            Position(1, column),
            PieceFactory::createPiece(
                PieceType::Pawn,
                Color::Black
            )
        );
    }

    // White pawns
    for (int column = 0; column < BoardSize; ++column) {
        setPiece(
            Position(6, column),
            PieceFactory::createPiece(
                PieceType::Pawn,
                Color::White
            )
        );
    }

    // White back rank
    const PieceType whiteBackRank[BoardSize] = {
        PieceType::Rook,
        PieceType::Knight,
        PieceType::Bishop,
        PieceType::Queen,
        PieceType::King,
        PieceType::Bishop,
        PieceType::Knight,
        PieceType::Rook
    };

    for (int column = 0; column < BoardSize; ++column) {
        setPiece(
            Position(7, column),
            PieceFactory::createPiece(
                whiteBackRank[column],
                Color::White
            )
        );
    }
}

bool Board::movePiece(Position from, Position to)
{
    if(!from.isValid() || !to.isValid())
        return false;

    if(from == to)
        return false;

    if(!pieceAt(from))
        return false;

    auto piece = std::move(
        cells_[from.row()][from.col()]
    );

    // Capture whatever is at the destination
    cells_[to.row()][to.col()] = std::move(piece);
    return true;
}

void Board::clear()
{
    for (int row = 0; row < BoardSize; ++row) {
        for (int column = 0; column < BoardSize; ++column) {
            cells_[row][column].reset();
        }
    }
}
