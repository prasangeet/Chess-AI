#include "game/pieces/King.hpp"
#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Piece.hpp"
#include "game/PieceType.hpp"
#include "game/Position.hpp"
#include <array>
#include <utility>
#include <vector>
King::King(Color color)
    : Piece(color, PieceType::King)
{
}

std::vector<Position> King::validMoves(
    const Board& board,
    const Position& from
) const
{
    std::vector<Position> moves;

    if(!from.isValid())
        return moves;

    static constexpr std::array<std::pair<int, int>, 8> offsets = {
        std::make_pair(-1, -1),
        std::make_pair(-1, 0),
        std::make_pair(-1, 1),
        std::make_pair(0, -1),
        std::make_pair(0, 1),
        std::make_pair(1, -1),
        std::make_pair(1, 0),
        std::make_pair(1, 1),
    };

    for(const auto& [rowOffset, colOffset] : offsets){
        const Position target(
            from.row() + rowOffset,
            from.col() + colOffset
        );
        if(!target.isValid())
            continue;

        // if this square is empty, add it to the list of valid moves
        if(!board.pieceAt(target))
            moves.push_back(target);

        // Enemy pieces are valid targets
        else if(board.pieceAt(target)->color() != color())
            moves.push_back(target);
    }

    return moves;
}
