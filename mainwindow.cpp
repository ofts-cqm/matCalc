#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./vectorpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new VectorPage(ui->page_vector));
    ui->page_vector->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
