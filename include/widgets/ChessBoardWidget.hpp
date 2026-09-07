#pragma once

#include "controller/GameController.hpp"
#include "game/Board.hpp"
#include "game/Move.hpp"
#include <QGraphicsView>
#include <qgraphicsitem.h>
#include <qgraphicssvgitem.h>
#include <qgraphicsview.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class QGraphicsScene;
class QGraphicsSvgItem;

class ChessBoardWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit ChessBoardWidget(
        QWidget* parent = nullptr
    );

    void setBoard(Board& board);
    void setController(GameController* controller);

public slots:
    void refreshBoard();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void setupScene();
    void loadBoard();
    void loadPieces();
    void highlightSelectedSquare(Position position);
    void clearSelectedSquare();

    void highlightMoves(const std::vector<Move>& moves);
    void clearMoveHighlights();

    Board* board_;
    QGraphicsScene* scene_;
    GameController* controller_;
    QGraphicsSvgItem* selectedSquare_ = nullptr;
    std::vector<QGraphicsItem*> moveHighlights_;
};
