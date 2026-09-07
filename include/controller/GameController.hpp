#pragma once

#include "game/Game.hpp"
#include "game/Move.hpp"
#include "game/Position.hpp"

#include <QObject>
#include <qobject.h>
#include <qtmetamacros.h>
#include <vector>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);

    Game& game();
    const Game& game() const;

    void selectSquare(const Position pos);
    void makeMove(const Position from, const Position to);

    void undo();
    void redo();
    void resetGame();

    bool hasSelection() const;
    Position selectedSquare() const;

    std::vector<Move> selectedMoves() const;

signals:
    void boardChanged();
    void moveMade(Move move);
    void selectionChanged(Position position);
    void selectionCleared();

private:
    Game game_;

    bool hasSelection_;
    Position selectedSquare_;
};