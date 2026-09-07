#include "game/pieces/Queen.hpp"
#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Position.hpp"
#include <array>
#include <utility>
#include <vector>
Queen::Queen(Color color)
    : Piece(color, PieceType::Queen)
{
}

std::vector<Position> Queen::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if(!from.isValid())
        return moves;

    static constexpr std::array<std::pair<int, int>, 8> directions = {
        std::make_pair(1, 0),
        std::make_pair(-1, 0),
        std::make_pair(0, 1),
        std::make_pair(0, -1),
        std::make_pair(1, 1),
        std::make_pair(-1, 1),
        std::make_pair(1, -1),
        std::make_pair(-1, -1),
    };

    for(const auto& [rowDirection, colDirection] : directions){
        Position current = from;

        while(true){
            current = Position(
                current.row() + rowDirection,
                current.col() + colDirection
            );

            if(!current.isValid())
                break;

            const Piece* piece = board.pieceAt(current);

            // Empty position, add to valid moves
            if(piece == nullptr){
                moves.push_back(current);
                continue;
            }

            // Enemy piece can be captured
            if(piece->color() != color()){
                moves.push_back(current);
                break;
            }

            // Friendly piece, stop the search
            break;
        }

    }
    return moves;
}
