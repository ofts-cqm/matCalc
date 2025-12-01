#ifndef GENERICPANE_H
#define GENERICPANE_H

#include "abstractnumberpane.h"
#include "genericnumber.h"
#include <QObject>
#include <QStackedWidget>
#include <QWidget>

class GenericPane : public QStackedWidget, public AbstractNumberPane<GenericNumber>
{
    Q_OBJECT

public:
    GenericPane(QWidget *parent, NumberType initialDisplay, bool editable = true, QWidget *initialPage = nullptr);

    void display(GenericNumber number);

    void reconstructPage();

private:
    NumberType currentType;
    bool editable;
    std::unordered_map<NumberType, int> typeIndex;
};

#endif // GENERICPANE_H
