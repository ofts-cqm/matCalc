#include "volatilestackedwidget.h"

VolatileStackedWidget::VolatileStackedWidget(QWidget *parent): QStackedWidget(parent) {}

QSize VolatileStackedWidget::sizeHint() const {
    if (currentWidget())
        return currentWidget()->sizeHint();
    return QStackedWidget::sizeHint();
}
