#include "game/pieces/Pawn.hpp"

#include "game/Board.hpp"
#include "game/Position.hpp"

#include <vector>

Pawn::Pawn(Color color)
    : Piece(color, PieceType::Pawn)
{
}

std::vector<Position> Pawn::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if (!from.isValid())
        return moves;

    const int direction =
        color() == Color::White ? -1 : 1;

    const int startingRow =
        color() == Color::White ? 6 : 1;

    // --------------------------------------------------------
    // One square forward
    // --------------------------------------------------------

    const Position oneStep(
        from.row() + direction,
        from.col()
    );

    if (
        oneStep.isValid() &&
        board.pieceAt(oneStep) == nullptr
    ) {
        moves.push_back(oneStep);

        // ----------------------------------------------------
        // Two squares forward
        // ----------------------------------------------------

        if (from.row() == startingRow) {
            const Position twoSteps(
                from.row() + 2 * direction,
                from.col()
            );

            if (
                twoSteps.isValid() &&
                board.pieceAt(twoSteps) == nullptr
            ) {
                moves.push_back(twoSteps);
            }
        }
    }

    // --------------------------------------------------------
    // Diagonal captures
    // --------------------------------------------------------

    const Position left(
        from.row() + direction,
        from.col() - 1
    );

    const Position right(
        from.row() + direction,
        from.col() + 1
    );

    if (left.isValid()) {
        const Piece* piece = board.pieceAt(left);

        if (piece != nullptr && piece->color() != color())
            moves.push_back(left);
    }

    if (right.isValid()) {
        const Piece* piece = board.pieceAt(right);

        if (piece != nullptr && piece->color() != color())
            moves.push_back(right);
    }

    return moves;
}
