#include "game/MoveValidator.hpp"

#include "game/Board.hpp"
#include "game/Game.hpp"
#include "game/Piece.hpp"

std::vector<Move> MoveValidator::legalMoves(
    const Game& game,
    Position from
)
{
    const Board& board = game.board();

    const Piece* piece = board.pieceAt(from);

    if (!piece)
        return {};

    const auto positions =
        piece->validMoves(board, from);

    std::vector<Move> moves;
    moves.reserve(positions.size());

    for (const Position& to : positions) {
        const Piece* target = board.pieceAt(to);

        // Cannot capture your own piece.
        if (target && target->color() == piece->color())
            continue;

        moves.emplace_back(from, to);
    }

    return moves;
}

bool MoveValidator::isLegalMove(
    const Game& game,
    const Move& move
)
{
    if (!move.from().isValid() ||
        !move.to().isValid())
        return false;

    const Board& board = game.board();

    const Piece* piece =
        board.pieceAt(move.from());

    if (!piece)
        return false;

    const auto moves =
        legalMoves(game, move.from());

    for (const Move& legalMove : moves) {
        if (legalMove.to() == move.to())
            return true;
    }

    return false;
}
