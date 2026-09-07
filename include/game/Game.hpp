#pragma once

#include "game/Board.hpp"
#include "game/Color.hpp"
#include "game/Move.hpp"
#include "game/Position.hpp"
#include <vector>
    
class Game {
public:
    Game();

    Board& board();
    const Board& board() const;

    Color currentTurn() const;

    std::vector<Move> legalMoves(const Position from) const;

    bool makeMove(const Position from, const Position to);

    void reset();

private:
    Board board_;
    Color currentTurn_{Color::White};
};
