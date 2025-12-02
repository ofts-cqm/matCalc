#ifndef ABSTRACTNUMBERPANE_H
#define ABSTRACTNUMBERPANE_H


#include "genericnumber.h"
#include <QtWidgets/qwidget.h>
class AbstractNumberPane
{
public:
    AbstractNumberPane(){}

    AbstractNumberPane(GenericNumber value){
        this->genericValue = value;
    }

    virtual void reconstructPage(){}

    virtual void display(GenericNumber num){}

    virtual const GenericNumber& getValue(){ return genericValue; }

    virtual const NumberType getType() const {return genericValue.getType();
}

protected:
    GenericNumber genericValue = GenericNumber::unknown;
};

#endif // ABSTRACTNUMBERPANE_H
