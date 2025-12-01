#ifndef NUMBERPANE_H
#define NUMBERPANE_H

#include "abstractnumberpane.h"
#include "decimallineedit.h"
#include <QObject>
#include <QWidget>

class NumberPane: public DecimalLineEdit, public AbstractNumberPane<double>
{
    Q_OBJECT
public:
    NumberPane(QWidget *parent, double value = 0, bool editable = true);

    virtual void reconstructPage();

    virtual void display(double num);

private:
    bool editable;
};

#endif // NUMBERPANE_H
