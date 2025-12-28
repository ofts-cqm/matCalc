#ifndef VOLATILESTACKEDWIDGET_H
#define VOLATILESTACKEDWIDGET_H

#include <QObject>
#include <QStackedWidget>

class VolatileStackedWidget : public QStackedWidget
{
public:
    VolatileStackedWidget(QWidget *parent = nullptr);

    virtual QSize sizeHint() const override;
};

#endif // VOLATILESTACKEDWIDGET_H
