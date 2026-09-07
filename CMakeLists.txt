cmake_minimum_required(VERSION 3.21)

project(ChessAI
    VERSION 0.1
    LANGUAGES CXX
)

# ============================================================
# C++ Configuration
# ============================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for clangd / Zed
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ============================================================
# Qt Configuration
# ============================================================

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Svg
    SvgWidgets
)


# ============================================================
# Application
# ============================================================

qt_add_executable(ChessAI

    # ========================================================
    # Application Entry Point
    # ========================================================

    src/main.cpp


    # ========================================================
    # Game Engine
    # ========================================================

    src/game/Game.cpp
    include/game/Game.hpp

    src/game/Board.cpp
    include/game/Board.hpp

    src/game/Piece.cpp
    include/game/Piece.hpp

    include/game/Color.hpp
    include/game/PieceType.hpp
    include/game/Position.hpp

    src/game/Move.cpp
    include/game/Move.hpp

    src/game/MoveValidator.cpp
    include/game/MoveValidator.hpp


    # ========================================================
    # Chess Pieces
    # ========================================================

    src/game/pieces/Pawn.cpp
    include/game/pieces/Pawn.hpp

    src/game/pieces/Knight.cpp
    include/game/pieces/Knight.hpp

    src/game/pieces/Bishop.cpp
    include/game/pieces/Bishop.hpp

    src/game/pieces/Rook.cpp
    include/game/pieces/Rook.hpp

    src/game/pieces/Queen.cpp
    include/game/pieces/Queen.hpp

    src/game/pieces/King.cpp
    include/game/pieces/King.hpp

    src/game/PieceFactory.cpp
    include/game/PieceFactory.hpp

    # ========================================================
    # Controller
    # ========================================================

    src/controller/GameController.cpp
    include/controller/GameController.hpp


    # ========================================================
    # Main Window
    # ========================================================

    src/ui/MainWindow.cpp
    include/ui/MainWindow.hpp

    src/ui/MainWindow.ui


    # ========================================================
    # Custom Widgets
    # ========================================================

    src/widgets/ChessBoardWidget.cpp
    include/widgets/ChessBoardWidget.hpp

    src/widgets/ChessPieceItem.cpp
    include/widgets/ChessPieceItem.hpp


    # ========================================================
    # Qt Resources
    # ========================================================

    resources/resources.qrc
)


# ============================================================
# Include Directories
# ============================================================

target_include_directories(ChessAI
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# ============================================================
# Qt Libraries
# ============================================================

target_link_libraries(ChessAI
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Svg
        Qt6::SvgWidgets
)
