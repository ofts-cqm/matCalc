#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QFrame>
#include "calculationhistory.h"

namespace Ui {
class HistoryItem;
}

class HistoryItem : public QFrame
{
    Q_OBJECT

public:
    explicit HistoryItem(const History::CalculationHistory *item, QWidget *parent = nullptr);
    ~HistoryItem();

    History::CalculationHistory itemBase;
    Calculation *calcBase;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void op1Pressed();
    void op2Pressed();
    void op3Pressed();

private:
    Ui::HistoryItem *ui;  
};

#endif // HISTORYITEM_H
