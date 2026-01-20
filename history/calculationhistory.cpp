#include "calculationhistory.h"
#include "../mainwindow.h"
#include "historywindow.h"
#include "historywriter.h"
#include <QJsonArray>

using namespace History;

CalculationHistory::CalculationHistory(const QJsonObject &cache)
    : page(static_cast<Page>(cache["page"].toInt())), operandA(cache["operandA"].toObject()),
    operandB(cache["operandB"].toObject()), result(cache["operandC"].toObject())
{
    QString sign = cache["sign"].toString();
    for (const SignDefinition &definition : signs){
        if (definition.literal == sign){
            this->sign = definition.sign;
            return;
        }
    }
    throw std::invalid_argument(sign.toStdString() + " does not match any sign");
}

CalculationHistory::CalculationHistory(Page page, Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res)
    : page(page), sign(sign), operandA(op1), operandB(op2), result(res) {}

Calculation *CalculationHistory::getCalculation() const{
    return new Calculation{
        .operandA = operandA.getType(),
        .operandB = operandB.getType(),
        .result = result.getType(),
        .sign = sign,
        .name = ""
    };
}

QJsonObject CalculationHistory::toJson() const{
    return
    {
        { "operandA", operandA.toJson() },
        { "operandB", operandB.toJson() },
        { "operandC", result.toJson() },
        { "sign", signs[sign].literal },
        { "page", std::to_underlying(page) }
    };
}

void History::addHistory(Page page, Sign sign, const GenericNumber &op1, const GenericNumber &op2, const GenericNumber &res){
    CalculationHistory history(page, sign, op1, op2, res);
    histories.push_back(history);
    HistoryWindow::instance->refreshHistory();
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

    writeToFile(jsons);
}

std::vector<CalculationHistory> History::histories = {};

static bool errorOccurred = false;

bool History::historyReady = false;

static void writeHistoryToGenericToken(const QJsonValue &record){
    try{
        histories.push_back(CalculationHistory(record.toObject()));
    }catch(std::exception &e){
        qWarning() << "Error When Restoring Calculation History:\n" << e.what();
        errorOccurred = true;
    }
}

void History::restoreHistory(){
    errorOccurred = false;
    histories.clear();
    std::for_each(jsons.cbegin(), jsons.cend(), writeHistoryToGenericToken);
    if (errorOccurred) MainWindow::setMessage("Error When Restoring Calculation History");
    historyReady = true;
}

bool History::loadHistory(){
    jsons = loadFromFile();
    restoreHistory();
    return writeFile;
}
