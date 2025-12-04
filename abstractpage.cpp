#include "abstractpage.h"
#include <QtWidgets/qboxlayout.h>

AbstractPage::AbstractPage(Evaluator evaluator, Calculation defaultCalculation, QWidget *parent)
    : QWidget(parent){
    this->evaluator = evaluator;
    this->currentCalculation = defaultCalculation;
    this->sign = new SignPane(defaultCalculation.sign, this);

    QVBoxLayout *main = new QVBoxLayout(this);
    this->setLayout(main);

    this->control = new QHBoxLayout(this);
    main->addLayout(control);

    this->content = new QHBoxLayout(this);
    main->addLayout(content);
}

