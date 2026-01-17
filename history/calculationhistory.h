#ifndef CALCULATIONHISTORY_H
#define CALCULATIONHISTORY_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include "../calculator_basic.h"
namespace History{

    struct CalculationHistory {
        GenericNumber operandA;
        GenericNumber operandB;
        GenericNumber result;
        Sign sign;

        CalculationHistory() = default;

        CalculationHistory(Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res);

        explicit CalculationHistory(const QJsonObject &cache);

        QJsonObject toJson() const;
    };

    static std::vector<CalculationHistory> histories;
    static QJsonArray jsons;

    void loadHistory();

    void addHistory(Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res);

    void restoreHistory(const QJsonArray &array);
}

#endif // CALCULATIONHISTORY_H
