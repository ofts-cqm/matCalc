#ifndef _UTIL_H
#define _UTIL_H

#include "abstractnumberpane.h"
#include "genericnumber.h"
#include "incompatiblepasteexception.h"
#include <QString>
#include <QtGui/qfont.h>
#include <QLayout>

QString format(double val);

std::string nameForNumberType(NumberType type);

QFont getLargeFont();
QFont getXLFont();

void clearLayout(QLayout *layout, bool deleteWidgets = true);

std::optional<double> numberParser(QStringView s);

QSpacerItem *getHorizontalSpacer();
QSpacerItem *getVerticalSpacer();

bool isZero(double d);

void throwRangeException(int accessed, int maximum) noexcept(false);

class EmptyPane : public AbstractNumberPane{
public:
    EmptyPane(QWidget *parent);

    virtual void reconstructPage() override {}
    virtual void display(GenericNumber num) override {}
    virtual void paste(GenericNumber num) override {
        throw IncompatiblePasteException(*this, num);
    }

};

AbstractNumberPane *getNewPageOfThisType(NumberType type, QWidget *parent, bool editable = true);

#endif // _UTIL_H
