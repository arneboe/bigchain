#include "mainwindow.h"
#include <QApplication>
#include <string>

int main(int argc, char *argv[])
{
    Q_ASSERT(argc == 2);
    const std::string ttyName(argv[1]);
    QApplication a(argc, argv);
    MainWindow w(ttyName);
    w.show();

    return a.exec();
}
