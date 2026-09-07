#include "ui/MainWindow.hpp"

#include "controller/GameController.hpp"
#include "ui_MainWindow.h"
#include "widgets/ChessBoardWidget.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    ui_->board->setBoard(controller_.game().board());
    ui_->board->setController(&controller_);

    connect(
        &controller_,
        &GameController::boardChanged,
        ui_->board,
        &ChessBoardWidget::refreshBoard
    );
}

MainWindow::~MainWindow()
{
    delete ui_;
}
