#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./vectorpane.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    VectorPane *vec = new VectorPane(ui->page_vector, {1, 2, 3});
    QLayout *layout = new QHBoxLayout(ui->page_vector);
    layout->addWidget(vec);
    ui->page_vector->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
