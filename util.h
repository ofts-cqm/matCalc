#ifndef _UTIL_H
#define _UTIL_H

#include "abstractnumberpane.h"
#include "genericnumber.h"
#include <QString>
#include <QtGui/qfont.h>
#include <QLayout>

QString format(double val);

QFont getLargeFont();
QFont getXLFont();

void clearLayout(QLayout *layout, bool deleteWidgets = true);

std::optional<double> numberParser(QStringView s);

QSpacerItem *getHorizontalSpacer();
QSpacerItem *getVerticalSpacer();

class EmptyPane : public AbstractNumberPane{
public:
    EmptyPane(QWidget *parent);
};

AbstractNumberPane *getNewPageOfThisType(NumberType type, QWidget *parent, bool editable = true);

#endif // _UTIL_H
