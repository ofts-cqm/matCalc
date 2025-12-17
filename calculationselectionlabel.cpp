#include "calculationselectionlabel.h"
#include "mainwindow.h"

CalculationSelectionLabel::CalculationSelectionLabel(
    const QString name, const Calculation *calculation, AbstractPage *page, QWidget *parent
    ) : QLabel(name, parent){
    this->calculation = calculation;
    this->page = page;
    //this->setMaximumHeight(20);
    //this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void CalculationSelectionLabel::mousePressEvent(QMouseEvent* event){
    MainWindow::setPage(this->page);
    page->switchTo(this->calculation);
    QLabel::mousePressEvent(event);
}
