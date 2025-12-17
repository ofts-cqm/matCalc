#ifndef CALCULATIONSELECTIONLABEL_H
#define CALCULATIONSELECTIONLABEL_H

#include "abstractpage.h"
#include "calculator_basic.h"
#include <QLabel>

class CalculationSelectionLabel: public QLabel
{
    Q_OBJECT;

public:
    CalculationSelectionLabel(const QString name, const Calculation *calculation, AbstractPage *page, QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    const Calculation *calculation;
    AbstractPage *page;
};

#endif // CALCULATIONSELECTIONLABEL_H
