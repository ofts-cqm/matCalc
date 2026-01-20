//#include "mainwindow.h"

#include <QApplication>

#include "calc/calculator.h"
#include "history/historywindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Calculator::init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    HistoryWindow h;
    h.show();

    return a.exec();
}
