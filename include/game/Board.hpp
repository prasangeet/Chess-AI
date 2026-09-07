#pragma once

#include "game/Position.hpp"

#include <array>
#include <memory>

class Piece;

class Board
{
public:
    Board();
    ~Board();

    Piece* pieceAt(Position position);
    const Piece* pieceAt(Position position) const;

    void setPiece(
        Position position,
        std::unique_ptr<Piece> piece
    );

    std::unique_ptr<Piece> removePiece(Position position);

    bool movePiece(Position from, Position to);
    void clear();
    void setUpInitialPosition();

private:
    static constexpr int BoardSize = 8;

    std::array<
        std::array<std::unique_ptr<Piece>, BoardSize>,
        BoardSize
    > cells_;
};
