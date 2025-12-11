#ifndef ABSTRACTNUMBERPANE_H
#define ABSTRACTNUMBERPANE_H


#include "genericnumber.h"
#include <QtWidgets/qwidget.h>
class AbstractNumberPane : public QWidget
{
Q_OBJECT

public:
    AbstractNumberPane(QWidget *parent) : QWidget(parent){}

    virtual void reconstructPage(){}

    virtual void display(GenericNumber num){}

    virtual const GenericNumber *getValue() {return &genericValue; }

    virtual const NumberType getType() const {
        return genericValue.getType();
    }

protected:
    GenericNumber genericValue;
};

#endif // ABSTRACTNUMBERPANE_H
