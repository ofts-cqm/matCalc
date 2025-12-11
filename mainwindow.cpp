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

    for (QLayout* layout : ui->mainFrame->findChildren<QLayout*>()) {
        QMargins m = layout->contentsMargins();
        bool isDefault =
            m.left()   == 12 &&
            m.top()    == 12 &&
            m.right()  == 12 &&
            m.bottom() == 12;

        if (isDefault) layout->setContentsMargins(0, 0, 0, 0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
