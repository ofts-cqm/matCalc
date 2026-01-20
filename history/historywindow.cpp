#include "historywindow.h"
#include "../util.h"
#include "calculationhistory.h"
#include "historyitem.h"
#include <QtWidgets/qboxlayout.h>
#include <QPushButton>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>

using namespace History;

HistoryWindow::HistoryWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setGeometry(0, 0, 300, 500);

    QScrollArea *wrapper = new QScrollArea(this);
    wrapper->setGeometry(0, 0, 300, 500);
    wrapper->setWidgetResizable(false);

    this->content = new QWidget(wrapper);
    this->content->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->content->setLayout(contentLayout = new QVBoxLayout());

    wrapper->setWidget(content);
    instance = this;
    refreshHistory();
}

void HistoryWindow::refreshHistory(){
    clearLayout(contentLayout);

    if (!History::historyReady){
        QLabel *label = new QLabel("Loading Histories...");
        contentLayout->addWidget(label);
        this->content->setMinimumSize(295, 42);
        return;
    }

    const std::vector<CalculationHistory> histories = History::histories;

    if (histories.size() == 0){
        QLabel *label = new QLabel("No Histories Yet");
        contentLayout->addWidget(label);
        this->content->setMinimumSize(295, 42);
        return;
    }

    for (const CalculationHistory &history : histories){
        contentLayout->addWidget(new HistoryItem(&history, content));
    }
    this->content->setMinimumSize(295, 12 + (80 + 24) * histories.size());
}

HistoryWindow *HistoryWindow::instance = nullptr;
