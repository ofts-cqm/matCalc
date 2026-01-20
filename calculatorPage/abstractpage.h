#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QObject>
#include <QWidget>
#include "../panes/controlpane.h"
#include "../genericnumber.h"
#include "../calculator_basic.h"
#include "../panes/genericpane.h"
#include "../panes/signpane.h"
#include "../history/calculationhistory.h"
#include "../history/historyitem.h"
#include <functional>

using Evaluator = std::function<GenericNumber *(const Calculation *, const GenericNumber *, const GenericNumber *)>;

class AbstractPage: public QWidget
{
    Q_OBJECT

public:
    AbstractPage(Evaluator evaluator, const Calculation *defaultCalculation, History::Page page, QWidget *parent = nullptr);

    GenericPane *registerOperand(GenericPane *operand, int position);

    virtual void switchTo(const Calculation *nextCalculation);

    void restore(const HistoryItem &history);

    void evaluate(bool record = false);

    static AbstractPage *getCurrent();

protected:
    Evaluator evaluator;
    SignPane *sign, *equal;
    const Calculation *currentCalculation;
    GenericPane *operandA, *operandB, *resultPane;
    QLayout *content;
    ControlPane *control;
    static AbstractPage *currentPage;
    History::Page page;
};

#endif // ABSTRACTPAGE_H
