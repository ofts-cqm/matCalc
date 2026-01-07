#ifndef NUMBERPANE_H
#define NUMBERPANE_H

#include "abstractnumberpane.h"
#include "decimallineedit.h"
#include <QObject>
#include <QWidget>

class NumberPane: public AbstractNumberPane
{
    Q_OBJECT
public:
    NumberPane(QWidget *parent, double value = 0, bool editable = true);

    virtual void reconstructPage();

    virtual void display(GenericNumber num);

    virtual void paste(GenericNumber num) {display(num);}

    virtual const GenericNumber *getValue();

private:
    bool editable;
    double value;
    DecimalLineEdit *content;
};

#endif // NUMBERPANE_H
