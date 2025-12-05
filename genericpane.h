#ifndef GENERICPANE_H
#define GENERICPANE_H

#include "abstractnumberpane.h"
#include "calculator_basic.h"
#include "genericnumber.h"
#include <QObject>
#include <QStackedWidget>
#include <QWidget>
#include <QtWidgets/qpushbutton.h>

class GenericPane : public QWidget
{
    Q_OBJECT

public:
    GenericPane(QWidget *parent, NumberType initialDisplay, bool editable = true);
    GenericPane(QWidget *parent, AbstractNumberPane *initialPage, bool editable = true);

    void display(GenericNumber number);

    void switchTo(NumberType type);

    void applyBorder(SignDefinition type);

    void reconstructPage();

    const GenericNumber& getValue();

    const NumberType getType() const;

private:
    QStackedWidget *content;
    NumberType currentType;
    bool editable;
    QPushButton *copy, *paste;
    std::unordered_map<NumberType, int> typeIndex;

    const static QString functionStyle, modulusStyle;
};

#endif // GENERICPANE_H
