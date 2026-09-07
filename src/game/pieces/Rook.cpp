

#include "game/pieces/Rook.hpp"
#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Piece.hpp"
#include "game/Position.hpp"
#include <array>
#include <utility>
#include <vector>
Rook::Rook(Color color)
    : Piece(color, PieceType::Rook)
{
}

std::vector<Position> Rook::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if(!from.isValid())
        return moves;

    static constexpr std::array<std::pair<int, int>, 4> directions = {
        std::make_pair(1, 0),
        std::make_pair(-1, 0),
        std::make_pair(0, 1),
        std::make_pair(0, -1),
    };

    for(const auto& [rowDirection, colDirection] : directions) {
        Position current = from;

        while(true) {
            current = Position(
                current.row() + rowDirection,
                current.col() + colDirection
            );

            if(!current.isValid())
                break;

            const Piece* piece = board.pieceAt(current);

            // Empty square
            if(piece == nullptr) {
                moves.push_back(current);
                continue;
            }

            // Enemy piece can be captured
            if(piece->color() != color())
                moves.push_back(current);

            break;
        }
    }

    return moves;
}
