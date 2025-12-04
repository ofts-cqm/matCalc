#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QObject>
#include <QWidget>
#include "genericnumber.h"
#include "calculator_basic.h"
#include "genericpane.h"
#include "signpane.h"
#include <functional>

using Evaluator = std::function<GenericNumber(Calculation, GenericNumber, GenericNumber)>;

class AbstractPage: public QWidget
{
    Q_OBJECT

public:
    AbstractPage(Evaluator evaluator, Calculation defaultCalculation, QWidget *parent = nullptr);

    GenericPane *registerOperand(GenericPane *operand, int position);

    virtual void switchTo(Calculation nextCalculation);

    void evaluate();

private:
    Evaluator evaluator;
    SignPane *sign;
    Calculation currentCalculation;
    GenericPane *operandA, *operandB, *resultPane;
    QLayout *content, *control;
};

#endif // ABSTRACTPAGE_H
