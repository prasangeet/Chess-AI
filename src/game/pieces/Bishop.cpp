
#include "game/pieces/Bishop.hpp"
#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Piece.hpp"
#include "game/PieceType.hpp"
#include "game/Position.hpp"
#include <array>
#include <utility>
#include <vector>

Bishop::Bishop(Color color):
    Piece(color, PieceType::Bishop)
{
}

std::vector<Position> Bishop::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if(!from.isValid())
        return moves;

    static constexpr std::array<std::pair<int, int>, 4> offsets = {
        std::make_pair(1, 1),
        std::make_pair(1, -1),
        std::make_pair(-1, 1),
        std::make_pair(-1, -1),
    };

    for (const auto& [rowDirection, colDirection] : offsets) {
        Position current = from;

        while (true) {
            current = Position(
                current.row() + rowDirection,
                current.col() + colDirection
            );

            if(!current.isValid())
                break;

            const Piece* piece = board.pieceAt(current);

            // Empty square - keep going
            if(piece == nullptr){
                moves.push_back(current);
                continue;
            }

            // Enemy piece - capture and stop
            if(piece->color() != color()) {
                moves.push_back(current);
            }

            break;
        }
    }

    return moves;
}
