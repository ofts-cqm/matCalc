#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QObject>
#include <QWidget>
#include "abstractnumberpane.h"
#include "genericnumber.h"
#include "calculator_basic.h"
#include <functional>

using Evaluator = std::function<GenericNumber(Calculation, GenericNumber, GenericNumber)>;

class AbstractPage: public QWidget
{
    Q_OBJECT

public:
    AbstractPage(Evaluator evaluator, Calculation defaultCalculation, QWidget *parent = nullptr);

    AbstractNumberPane registerOperand(AbstractNumberPane operand, int position);

    virtual void switchTo(Calculation nextCalculation);

    void evaluate();

private:
    Evaluator evaluator;
    Calculation currentCalculation;
    AbstractNumberPane *operandA, *operandB, *resultPane;
};

#endif // ABSTRACTPAGE_H
