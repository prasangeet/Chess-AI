#pragma once

#include <QGraphicsSvgItem>

class Piece;

class ChessPieceItem final : public QGraphicsSvgItem
{
public:
    explicit ChessPieceItem(
        const Piece* piece,
        QGraphicsItem* parent = nullptr
    );

    const Piece* piece() const;

private:
    static QString assetPath(const Piece& piece);

    const Piece* piece_;
};
