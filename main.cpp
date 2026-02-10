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

/*
#include "numbers/polynomialmatrix.h"
#include <iostream>
int main(){
    Matrix raw(3, 3);
    raw[0, 0] = 1;
    raw[0, 1] = 2;
    raw[0, 2] = 3;
    raw[1, 0] = 4;
    raw[1, 1] = 7;
    raw[1, 2] = 5;
    raw[2, 0] = 4;
    raw[2, 1] = 8;
    raw[2, 2] = 1;
    PolynomialMatrix mat(raw);
    std::cout << mat.det().toString() << std::endl;
}*/
