#ifndef SIGNPANE_H
#define SIGNPANE_H


#include "calculator_basic.h"
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qwidget.h>
#include <QLabel>


class SignPane : public QWidget
{
    Q_OBJECT

public:

    SignPane(Sign sign, QWidget *parent);

    void display(Sign sign);

private:
    QLabel *label;

    QSpacerItem *topSpacer;
};

#endif // SIGNPANE_H
