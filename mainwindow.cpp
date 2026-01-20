#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculatorPage/vectorpage.h"
#include "calculatorPage/matrixpage.h"
#include "history/calculationhistory.h"
#include "history/historywriter.h"
#include "history/historywindow.h"

#include <QtConcurrent/QtConcurrent>
#include <QtGui/qevent.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MatCalc");
    this->ui->stackedWidget->addWidget(vecPage = (new VectorPage(ui->page_vector))->fillIndexPage(ui->bar_vector));
    this->ui->stackedWidget->addWidget(matPage = (new MatrixPage(ui->page_matrix))->fillIndexPage(ui->bar_matrix));
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

    auto future = QtConcurrent::run(History::loadHistory);
    auto *watcher = new QFutureWatcher<bool>();
    connect(watcher, &QFutureWatcher<bool>::finished, this, [=] {
        bool success = watcher->result();
        if (!success){
            History::promptFileAccess();
        }
        HistoryWindow::instance->refreshHistory();
    });
    watcher->setFuture(future);

    historyWindow = new HistoryWindow();
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::openHistory);
}

void MainWindow::setPage(AbstractPage *page){
    instance->ui->stackedWidget->setCurrentWidget(page);
}

void MainWindow::openHistory(){
    historyWindow->show();
}

AbstractPage *MainWindow::setPage(History::Page page){
    switch(page){
    case History::Page::VECTOR:
        instance->ui->stackedWidget->setCurrentWidget(instance->vecPage);
        break;
    case History::Page::MATRIX:
        instance->ui->stackedWidget->setCurrentWidget(instance->matPage);
    }

    return static_cast<AbstractPage *>(instance->ui->stackedWidget->currentWidget());
}

void MainWindow::setMessage(QString message){
    instance->ui->statusbar->showMessage(message, 3000);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QCoreApplication::quit();
    event->accept();
}

MainWindow *MainWindow::getInstance(){return instance;}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::instance = nullptr;
