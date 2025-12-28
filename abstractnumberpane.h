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

    // display: display the target number regardless if its a different form
    virtual void display(GenericNumber num){}

    // instead of display another number, this set the current number to the target number
    // which means this preserves the current type format, while display() does not
    virtual void paste(GenericNumber num){}

    virtual const GenericNumber *getValue() {return &genericValue; }

    virtual const NumberType getType() const {
        return genericValue.getType();
    }

    void setAsCurrent(bool current) { isCurrentPage = current; }

protected:
    GenericNumber genericValue;
    bool isCurrentPage;
};

#endif // ABSTRACTNUMBERPANE_H
