#include "numberpane.h"
#include "util.h"

NumberPane::NumberPane(QWidget *parent, double value, bool editable)
    : AbstractNumberPane(parent)
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

const GenericNumber *NumberPane::getValue(){
    this->genericValue = &value;
    return &genericValue;
}

void NumberPane::display(GenericNumber num){
    if (num.getType() != NUMBER) throw IncompatiblePasteException(*this, num);
    this->value = num.getDouble();
    this->content->setValue(num.getDouble());
}
