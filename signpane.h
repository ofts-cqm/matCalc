#ifndef SIGNPANE_H
#define SIGNPANE_H

#include "genericnumber.h"
#include "genericpane.h"
#include <QtWidgets/qwidget.h>
#include <QLabel>
#include <functional>

enum Sign{
    PLUS,
    MINUS,
    MUL,
    DOT,
    CROSS,
    PROJ,
    PERP,
    LENGTH,
    RREF,
    INVT,
    TRANS,
    NULL_SPACE,
    COL_SPACE,
    RANK,
    BASE,
    SOLVE
};

struct Calculation{
    NumberType operandA;
    NumberType operandB;
    NumberType result;
    Sign sign;
};

using Evaluator = std::function<GenericNumber(Calculation, GenericNumber, GenericNumber)>;

class SignPane : public QLabel
{
    Q_OBJECT

public:

    SignPane(Calculation calc, Evaluator eva, GenericPane *paneA, GenericPane *paneB, GenericPane *paneC);

    void switchToCalculation(Calculation calc);

protected:

    Sign currentSign;
    Calculation currentCalc;
    GenericPane *operandA;
    GenericPane *operandB;
    GenericPane *resultPane;
    Evaluator evaluator;
};

#endif // SIGNPANE_H
