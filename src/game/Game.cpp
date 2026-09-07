#include "game/Game.hpp"
#include "game/Color.hpp"
#include "game/Move.hpp"
#include "game/MoveValidator.hpp"
#include "game/Piece.hpp"
#include "game/Position.hpp"
#include <vector>

Game::Game()
    : board_()
{
}

Board& Game::board()
{
    return board_;
}

const Board& Game::board() const
{
    return board_;
}

Color Game::currentTurn() const {
    return currentTurn_;
}

std::vector<Move> Game::legalMoves(const Position from) const
{
    const Piece* piece = board_.pieceAt(from);

    if (!piece)
        return {};

    return MoveValidator::legalMoves(*this, from);
}

bool Game::makeMove(
    const Position from,
    const Position to
)
{
    const Move move(from, to);

    if (!MoveValidator::isLegalMove(*this, move))
        return false;

    const Piece* piece = board_.pieceAt(from);

    if (!piece)
        return false;

    if (piece->color() != currentTurn_)
        return false;

    if (!board_.movePiece(from, to))
        return false;

    currentTurn_ =
        currentTurn_ == Color::White
            ? Color::Black
            : Color::White;

    return true;
}

void Game::reset()
{
    board_.clear();
    board_.setUpInitialPosition();
    currentTurn_ = Color::White;
}
