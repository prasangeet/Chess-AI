#include "ui/MainWindow.hpp"
#include <qapplication.h>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
