#pragma once

class Position {
public:
    Position() = default;

    Position(int row, int col)
        : row_(row),
          col_(col)
    {
    }

    int row() const
    {
        return row_;
    }

    int col() const
    {
        return col_;
    }

    bool isValid() const
    {
        return row_ >= 0 &&
               row_ < 8 &&
               col_ >= 0 &&
               col_ < 8;
    }

    bool operator==(const Position& other) const
    {
        return row_ == other.row_ &&
               col_ == other.col_;
    }

    bool operator!=(const Position& other) const
    {
        return !(*this == other);
    }

private:
    int row_ = -1;
    int col_ = -1;
};
