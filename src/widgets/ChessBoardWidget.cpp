#include "widgets/ChessBoardWidget.hpp"
#include "controller/GameController.hpp"
#include "game/Piece.hpp"
#include "game/Position.hpp"
#include "widgets/ChessPieceItem.hpp"

#include <qevent.h>
#include <qframe.h>
#include <qgraphicsscene.h>
#include <qgraphicssvgitem.h>
#include <qgraphicsview.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpoint.h>
#include <qtypes.h>
#include <qwidget.h>
#include <QtSvgWidgets/QGraphicsSvgItem>

ChessBoardWidget::ChessBoardWidget(
    QWidget* parent
)
    : QGraphicsView(parent),
      scene_(new QGraphicsScene(this))
{
    setupScene();
    loadBoard();

    setScene(scene_);

    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setAlignment(Qt::AlignCenter);
}

void ChessBoardWidget::setupScene()
{
    scene_->setSceneRect(0, 0, 800, 800);
}

void ChessBoardWidget::setBoard(Board& board)
{
    board_ = &board;
    loadPieces();
}

void ChessBoardWidget::loadBoard()
{
    auto* board = new QGraphicsSvgItem(":/board.svg");

    const QRectF bounds = board->boundingRect();

    board->setScale(
        800.0 / bounds.width()
    );

    board->setPos(0, 0);

    scene_->addItem(board);
}


void ChessBoardWidget::loadPieces()
{
    if (!board_)
        return;

    constexpr int BoardSize = 8;
    constexpr qreal SquareSize = 100.0;

    for (int row = 0; row < BoardSize; ++row) {
        for (int column = 0; column < BoardSize; ++column) {

            const Position position(row, column);
            const Piece* piece = board_->pieceAt(position);

            if (!piece)
                continue;

            auto* pieceItem = new ChessPieceItem(piece);

            const QRectF bounds = pieceItem->boundingRect();

            const qreal x =
                column * SquareSize
                + (SquareSize - bounds.width()) / 2.0
                - bounds.left();

            const qreal y =
                row * SquareSize
                + (SquareSize - bounds.height()) / 2.0
                - bounds.top();

            pieceItem->setPos(x, y);

            pieceItem->setZValue(2);

            scene_->addItem(pieceItem);
        }
    }
}

void ChessBoardWidget::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);

    fitInView(
        scene_->sceneRect(),
        Qt::KeepAspectRatio
    );
}

void ChessBoardWidget::setController(GameController* controller)
{
    controller_ = controller;

    if(!controller_)
        return;

    connect(
        controller_,
        &GameController::selectionChanged,
        this,
        [this](Position position) {
            highlightSelectedSquare(position);
            highlightMoves(controller_->selectedMoves());
        }
    );

    connect(
        controller_,
        &GameController::selectionCleared,
        this,
        [this] {
            clearSelectedSquare();
            clearMoveHighlights();
        }
    );
}

void ChessBoardWidget::mousePressEvent(QMouseEvent* event)
{
    if(!controller_)
        return;

    if(event->button() != Qt::LeftButton)
        return;

    const QPointF scenePosition = mapToScene(event->position().toPoint());

    constexpr qreal SquareSize = 100.0;

    const int column = static_cast<int>(scenePosition.x() / SquareSize);
    const int row = static_cast<int>(scenePosition.y() / SquareSize);

    const Position position(row, column);

    if(!position.isValid())
        return;

    controller_->selectSquare(position);
}

void ChessBoardWidget::refreshBoard()
{
    if (!board_)
        return;

    const auto items = scene_->items();

    for (QGraphicsItem* item : items) {
        auto* pieceItem = dynamic_cast<ChessPieceItem*>(item);

        if (!pieceItem)
            continue;

        scene_->removeItem(pieceItem);
        delete pieceItem;
    }

    loadPieces();
}

void ChessBoardWidget::highlightSelectedSquare(Position position){
    clearSelectedSquare();

    constexpr qreal SquareSize = 100.0;

    const bool isDarkSquare =
        (position.row() + position.col()) % 2 == 1;

    const QString assetPath = isDarkSquare
        ? QStringLiteral(":/black_sq_select.svg")
        : QStringLiteral(":/white_sq_select.svg");

    selectedSquare_ = new QGraphicsSvgItem(assetPath);

    const QRectF bounds = selectedSquare_->boundingRect();

    selectedSquare_->setScale(
        SquareSize / bounds.width()
    );

    selectedSquare_->setPos(
        position.col() * SquareSize,
        position.row() * SquareSize
    );

    selectedSquare_->setZValue(1);

    scene_->addItem(selectedSquare_);
}

void ChessBoardWidget::clearSelectedSquare()
{
    if (!selectedSquare_)
        return;

    scene_->removeItem(selectedSquare_);
    delete selectedSquare_;
    selectedSquare_ = nullptr;
}

void ChessBoardWidget::clearMoveHighlights()
{
    for (auto* item : moveHighlights_) {
        scene_->removeItem(item);
        delete item;
    }
    moveHighlights_.clear();
}

void ChessBoardWidget::highlightMoves(const std::vector<Move>& moves)
{
    clearMoveHighlights();

    constexpr qreal SquareSize = 100.0;

    for (const Move& move : moves) {
        const Position position = move.to();

        if (!position.isValid())
            continue;

        const Piece* targetPiece = board_->pieceAt(position);

        // Enemy piece exists on destination square -> capture
        const bool isCapture = targetPiece != nullptr;

        if (isCapture) {
            auto* highlight = new QGraphicsRectItem(
                position.col() * SquareSize,
                position.row() * SquareSize,
                SquareSize,
                SquareSize
            );

            // Slight transparent red fill
            highlight->setBrush(
                QBrush(QColor(255, 0, 0, 40))
            );
            highlight->setPen(Qt::NoPen);

            highlight->setZValue(1);

            scene_->addItem(highlight);
            moveHighlights_.push_back(highlight);
        }
        else {
            const bool isDarkSquare =
                (position.row() + position.col()) % 2 == 1;

            const QString assetPath = isDarkSquare
                ? QStringLiteral(":/black_sq_move.svg")
                : QStringLiteral(":/white_sq_move.svg");

            auto* highlight = new QGraphicsSvgItem(assetPath);

            const QRectF bounds = highlight->boundingRect();

            highlight->setScale(
                SquareSize / bounds.width()
            );

            highlight->setPos(
                position.col() * SquareSize,
                position.row() * SquareSize
            );

            highlight->setZValue(1);

            scene_->addItem(highlight);
            moveHighlights_.push_back(highlight);
        }
    }
}
