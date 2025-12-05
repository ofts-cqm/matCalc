#include "numberpane.h"
#include "util.h"

NumberPane::NumberPane(QWidget *parent, double value, bool editable)
    : AbstractNumberPane(value, parent)
{
    this->value = value;
    this->setMinimumWidth(40);
    this->setMaximumWidth(160);

    QVBoxLayout *main = new QVBoxLayout(this);
    this->setLayout(main);

    main->addItem(getVerticalSpacer());
    main->addWidget(content = new DecimalLineEdit(numberParser, [this](double val){this->value = val;}, value, this));
    main->addItem(getVerticalSpacer());

    if (!editable) this->content->setReadOnly(true);
    this->editable = editable;
}

void NumberPane::reconstructPage(){
    this->content->setValue(this->value);
}

void NumberPane::display(double num){
    this->value = num;
    this->genericValue = num;
    this->content->setValue(num);
}
