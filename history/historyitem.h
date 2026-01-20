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

private:
    Ui::HistoryItem *ui;
    const History::CalculationHistory *itemBase;
};

#endif // HISTORYITEM_H
