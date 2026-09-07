#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Piece.hpp"
#include "game/Position.hpp"
#include "game/pieces/Knight.hpp"

#include <array>
#include <utility>
#include <vector>

Knight::Knight(Color color)
    : Piece(color, PieceType::Knight)
{
}

std::vector<Position> Knight::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if (!from.isValid())
        return moves;

    static constexpr std::array<std::pair<int, int>, 8> offsets = {
        std::make_pair(-2, -1),
        std::make_pair(-2,  1),
        std::make_pair(-1, -2),
        std::make_pair(-1,  2),
        std::make_pair( 1, -2),
        std::make_pair( 1,  2),
        std::make_pair( 2, -1),
        std::make_pair( 2,  1),
    };

    for (const auto& [rowOffset, colOffset] : offsets) {

        const Position target(
            from.row() + rowOffset,
            from.col() + colOffset
        );

        // Target is outside the board.
        if (!target.isValid())
            continue;

        const Piece* piece = board.pieceAt(target);

        // Empty square.
        if (piece == nullptr) {
            moves.push_back(target);
            continue;
        }

        // Opponent's piece.
        if (piece->color() != color())
            moves.push_back(target);
    }

    return moves;
}
