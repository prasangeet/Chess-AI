#pragma once

#include "game/Position.hpp"
class Move
{
public:
    Move(
        Position from,
        Position to
    );

    Position from() const;
    Position to() const;
private:
    Position from_;
    Position to_;
};
