#ifndef _UTIL_H
#define _UTIL_H

#include "genericnumber.h"
#include <QString>
#include <QtGui/qfont.h>
#include <QLayout>

QString format(double val);

QFont getLargeFont();

void clearLayout(QLayout *layout, bool deleteWidgets = true);

std::optional<double> numberParser(QStringView s);

QWidget *getNewPageOfThisType(NumberType type, QWidget *parent, bool editable = true);

#endif // _UTIL_H
