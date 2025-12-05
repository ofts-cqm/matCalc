#include "signpane.h"
#include "util.h"
#include <QVBoxLayout>

SignPane::SignPane(Sign sign, QWidget *parent): QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    topSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(topSpacer);
    label = new QLabel(this);
    label->setFont(getLargeFont());
    mainLayout->addWidget(label);
    mainLayout->addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    display(sign);
}

void SignPane::display(Sign sign){
    label->setText(signs[sign].literal);
    if (sign == INVT || sign == TRANS){
        topSpacer->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    }else{
        topSpacer->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    }
}
