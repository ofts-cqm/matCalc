#ifndef GENERICPANE_H
#define GENERICPANE_H

#include "abstractnumberpane.h"
#include "calculator_basic.h"
#include "genericnumber.h"
#include <QObject>
#include <QStackedWidget>
#include <QWidget>
#include <QtWidgets/qboxlayout.h>
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

    const GenericNumber *getValue();

    const NumberType getType() const;

private:
    struct Hasher{
        std::size_t operator()(const NumberType &type) const {
            return static_cast<std::size_t>(type);
        }
    };

    QStackedWidget *content;
    NumberType currentType;
    bool editable;
    QPushButton *copy, *paste;
    int typeIndex[NUMBER_TYPE_COUNT];
    const static QString functionStyle, modulusStyle;
    QHBoxLayout *buttons;
    QVBoxLayout *mainLayout;

private slots:
    void onCopy();
    void onPaste();
};

#endif // GENERICPANE_H
