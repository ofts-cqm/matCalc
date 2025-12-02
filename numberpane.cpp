#include "numberpane.h"
#include "util.h"

NumberPane::NumberPane(QWidget *parent, double value, bool editable)
    : DecimalLineEdit(numberParser, [this](double val){this->value = val;}, value, parent),
    AbstractNumberPane(value)
{
    this->value = value;
    if (!editable) this->setReadOnly(true);
    this->editable = editable;
}

void NumberPane::reconstructPage(){
    this->setValue(this->value);
}

void NumberPane::display(double num){
    this->value = num;
    this->genericValue = num;
    this->setValue(num);
}
