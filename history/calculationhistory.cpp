#include "calculationhistory.h"
#include "../mainwindow.h"
#include <QJsonArray>

using namespace History;

CalculationHistory::CalculationHistory(const QJsonObject &cache)
    : operandA(cache["operandA"].toObject()), operandB(cache["operandB"].toObject()), result(cache["operandC"].toObject()){
    QString sign = cache["sign"].toString();
    for (const SignDefinition &definition : signs){
        if (definition.literal == sign){
            this->sign = definition.sign;
            return;
        }
    }
    throw std::invalid_argument(sign.toStdString() + " does not match any sign");
}

CalculationHistory::CalculationHistory(Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res)
    : sign(sign), operandA(op1), operandB(op2), result(res) {}

QJsonObject CalculationHistory::toJson() const{
    return
    {
        { "operandA", operandA.toJson() },
        { "operandB", operandB.toJson() },
        { "operandC", result.toJson() },
        { "sign", signs[sign].literal }
    };
}

void addHistory(Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res){
    CalculationHistory history(sign, op1, op2, res);
    histories.push_back(history);
    try{
        jsons.push_back(history.toJson());
    }catch(std::exception &e){
        qWarning() << "Error When Stroing Calculation History:\n" << e.what();
        MainWindow::setMessage("Error When Writing Calculation History");
    }

    if (histories.size() > 20){
        histories.erase(histories.begin());
        jsons.erase(jsons.begin());
    }

    // call DocumentWriter to write history
}

static bool errorOccurred = false;

static void writeHistoryToGenericToken(const QJsonValue &record){
    try{
        histories.push_back(CalculationHistory(record.toObject()));
    }catch(std::exception &e){
        qWarning() << "Error When Restoring Calculation History:\n" << e.what();
        errorOccurred = true;
    }
}

void restoreHistory(const QJsonArray &array){
    errorOccurred = false;
    jsons = array;
    histories.clear();
    std::for_each(array.cbegin(), array.cend(), writeHistoryToGenericToken);
    if (errorOccurred) MainWindow::setMessage("Error When Restoring Calculation History");
}

void loadHistory(){

}
