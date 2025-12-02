#ifndef GENERICPANE_H
#define GENERICPANE_H

#include "abstractnumberpane.h"
#include "genericnumber.h"
#include <QObject>
#include <QStackedWidget>
#include <QWidget>

class GenericPane : public QStackedWidget, public AbstractNumberPane
{
    Q_OBJECT

public:
    GenericPane(QWidget *parent, NumberType initialDisplay, bool editable = true);
    GenericPane(QWidget *parent, QWidget *initialPage, bool editable = true);

    void display(GenericNumber number);

    void switchTo(NumberType type);

    void reconstructPage();

    const GenericNumber& getValue();

    const NumberType getType() const;

private:
    NumberType currentType;
    bool editable;
    std::unordered_map<NumberType, int> typeIndex;
};

#endif // GENERICPANE_H
