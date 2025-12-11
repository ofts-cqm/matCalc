#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QObject>
#include <QWidget>
#include "controlpane.h"
#include "genericnumber.h"
#include "calculator_basic.h"
#include "genericpane.h"
#include "signpane.h"
#include <functional>

using Evaluator = std::function<GenericNumber *(const Calculation *, const GenericNumber *, const GenericNumber *)>;

class AbstractPage: public QWidget
{
    Q_OBJECT

public:
    AbstractPage(Evaluator evaluator, const Calculation *defaultCalculation, QWidget *parent = nullptr);

    GenericPane *registerOperand(GenericPane *operand, int position);

    virtual void switchTo(const Calculation *nextCalculation);

    void evaluate();

    static AbstractPage *getCurrent();

protected:
    Evaluator evaluator;
    SignPane *sign;
    const Calculation *currentCalculation;
    GenericPane *operandA, *operandB, *resultPane;
    QLayout *content;
    ControlPane *control;
    static AbstractPage *currentPage;
};

#endif // ABSTRACTPAGE_H
