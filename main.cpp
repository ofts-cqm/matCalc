//#include "mainwindow.h"

#include <QApplication>

#include "calc/calculator.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Calculator::init();
    Calculator::debugMode = true;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
