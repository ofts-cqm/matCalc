#include "eigenpane.h"
#include "../util.h"
#include "spansetpane.h"
#include <QtWidgets/qlabel.h>

EigenPane::EigenPane(const EigenSpace &eigen, QWidget *parent)
    : AbstractNumberPane{parent}, currentIndex(0), eigen(eigen), sets()
{
    this->genericValue = eigen;
    content = new QVBoxLayout();
    this->setLayout(content);

    spaces = new QStackedWidget();
    content->addWidget(spaces);

    buttonBox = new QHBoxLayout();
    content->addLayout(buttonBox);

    prev = new QPushButton();
    prev->setText("Prev");
    connect(prev, &QPushButton::clicked, this, &EigenPane::onPrevPressed);
    buttonBox->addWidget(prev);

    buttonBox->addItem(getHorizontalSpacer());

    next = new QPushButton();
    next->setText("Next");
    connect(next, &QPushButton::clicked, this, &EigenPane::onNextPressed);
    buttonBox->addWidget(next);

    EigenPane::reconstructPage();
}

void EigenPane::switchPage(){
    sets[spaces->currentIndex()]->setAsCurrent(false);
    spaces->setCurrentIndex(currentIndex);
    sets[spaces->currentIndex()]->setAsCurrent(true);
}

QLabel *getCenterLabel(QString str){
    QLabel *label = new QLabel(str);
    label->setAlignment(Qt::AlignHCenter);
    label->setFont(getLargeFont());
    return label;
}

void EigenPane::reconstructPage(){
    this->currentIndex = 0;
    prev->setEnabled(false);
    next->setEnabled(eigen.size > 1);

    while (spaces->count()) {
        spaces->currentWidget()->deleteLater();
        spaces->removeWidget(spaces->currentWidget());
    }

    if (eigen.size == 0){
        spaces->addWidget(new QLabel("Theres No Eigen Space"));
        return;
    }

    sets.resize(eigen.size, nullptr);
    for (int i = 0; i < eigen.size; i++){
        QWidget *page = new QWidget();
        QVBoxLayout *pageLayout = new QVBoxLayout();
        pageLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
        page->setLayout(pageLayout);
        spaces->addWidget(page);

        pageLayout->addWidget(getCenterLabel("Eigen Value: " + format(eigen.eigenValues[i])));
        pageLayout->addWidget(sets[i] = new SpanSetPane(eigen.eigenSpaces[i], false, nullptr));
    }
    switchPage();
}

void EigenPane::display(GenericNumber num){
    this->genericValue = num;
    this->eigen = num.getEigen();
    reconstructPage();
}

void EigenPane::paste(GenericNumber num){}

void EigenPane::onPrevPressed(){
    if (this->currentIndex == 0) return;
    currentIndex--;
    switchPage();
    if (this->currentIndex == 0) prev->setEnabled(false);
    if (spaces->count() != 1) next->setEnabled(true);
}

void EigenPane::onNextPressed(){
    if (this->currentIndex == spaces->count() - 1) return;
    currentIndex++;
    switchPage();
    if (this->currentIndex == spaces->count() - 1) next->setEnabled(false);
    if (spaces->count() != 1) prev->setEnabled(true);
}
