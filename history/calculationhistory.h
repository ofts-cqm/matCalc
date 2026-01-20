#ifndef CALCULATIONHISTORY_H
#define CALCULATIONHISTORY_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include "../calculator_basic.h"
namespace History{

    enum class Page{
        VECTOR,
        MATRIX
    };

    struct CalculationHistory {
        GenericNumber operandA;
        GenericNumber operandB;
        GenericNumber result;
        Sign sign;
        Page page;

        CalculationHistory() = default;

        CalculationHistory(Page page, Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res);

        explicit CalculationHistory(const QJsonObject &cache);

        Calculation *getCalculation() const;

        QJsonObject toJson() const;
    };

    extern std::vector<CalculationHistory> histories;
    static QJsonArray jsons = {};
    extern bool historyReady;

    bool loadHistory();

    void addHistory(Page page, Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res);

    void restoreHistory();
}

#endif // CALCULATIONHISTORY_H
