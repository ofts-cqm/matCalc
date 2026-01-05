#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./vectorpage.h"
#include "matrixpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QLayout *layout = new QHBoxLayout();
    //layout->addWidget((new VectorPage(ui->page_vector))->fillIndexPage(ui->bar_vector));
    //ui->page_vector->setLayout(layout);
    this->ui->stackedWidget->addWidget((new VectorPage(ui->page_vector))->fillIndexPage(ui->bar_vector));
    this->ui->stackedWidget->addWidget((new MatrixPage(ui->page_matrix))->fillIndexPage(ui->bar_matrix));
    this->ui->stackedWidget->setCurrentIndex(2);

    for (QLayout* layout : ui->mainFrame->findChildren<QLayout*>()) {
        QMargins m = layout->contentsMargins();
        bool isDefault =
            m.left()   == 12 &&
            m.top()    == 12 &&
            m.right()  == 12 &&
            m.bottom() == 12;

        if (isDefault) layout->setContentsMargins(0, 0, 0, 0);
    }

    instance = this;
}

void MainWindow::setPage(AbstractPage *page){
    instance->ui->stackedWidget->setCurrentWidget(page);
}

void MainWindow::setMessage(QString message){
    instance->ui->statusbar->showMessage(message, 3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::instance = nullptr;
