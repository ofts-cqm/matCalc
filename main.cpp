//#include "mainwindow.h"

#include <QApplication>

#include "calc/calculator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    init();
    std::string error;
    debugMode = true;
    auto res = evaluate("(1 + 2) * 3", error);
    std::cout << res.value_or(-1) << std::endl;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
