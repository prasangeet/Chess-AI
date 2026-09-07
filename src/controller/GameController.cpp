#include "controller/GameController.hpp"
#include "game/Game.hpp"
#include "game/Piece.hpp"

GameController::GameController(QObject* parent)
    : QObject(parent),
      game_(),
      hasSelection_(false),
      selectedSquare_(-1, -1)
{
}

Game& GameController::game()
{
    return game_;
}

const Game& GameController::game() const
{
    return game_;
}

void GameController::selectSquare(Position position)
{
    if (!position.isValid())
        return;

    // No piece is currently selected.
    if (!hasSelection_) {
        const Piece* piece = game_.board().pieceAt(position);

        if (!piece)
            return;

        if (piece->color() != game_.currentTurn())
            return;

        hasSelection_ = true;
        selectedSquare_ = position;

        emit selectionChanged(position);

        return;
    }

    // Clicking the currently selected square clears selection.
    if (position == selectedSquare_) {
        hasSelection_ = false;
        selectedSquare_ = Position(-1, -1);

        emit selectionCleared();

        return;
    }

    // Try to move the selected piece.
    makeMove(selectedSquare_, position);
}

void GameController::makeMove(
    Position from,
    Position to
)
{
    if (!game_.makeMove(from, to))
        return;

    hasSelection_ = false;
    selectedSquare_ = Position(-1, -1);

    emit boardChanged();
    emit moveMade(Move(from, to));
    emit selectionCleared();
}

bool GameController::hasSelection() const
{
    return hasSelection_;
}

Position GameController::selectedSquare() const
{
    return selectedSquare_;
}

std::vector<Move> GameController::selectedMoves() const
{
    if (!hasSelection_)
        return {};

    return game_.legalMoves(selectedSquare_);
}

void GameController::undo()
{
    // Implement when MoveHistory is connected.
}

void GameController::redo()
{
    // Implement when MoveHistory is connected.
}

void GameController::resetGame()
{
    game_.reset();

    hasSelection_ = false;
    selectedSquare_ = Position(-1, -1);

    emit boardChanged();
    emit selectionCleared();
}
