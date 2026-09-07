#include "game/Move.hpp"
#include "game/Position.hpp"
Move::Move(Position from, Position to)
    : from_(from)
    , to_(to)
{
}

Position Move::from() const
{
    return from_;
}   

Position Move::to() const
{
    return to_;
}
