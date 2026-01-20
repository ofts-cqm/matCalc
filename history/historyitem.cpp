#include "historyitem.h"
#include "history/ui_historyitem.h"
#include "../util.h"

using namespace History;

std::pair<QString, int> getMatrixStr(const Matrix& mat){
    std::vector<std::vector<QString>> allVal(mat.getHeight(), std::vector<QString>(mat.getWidth(), ""));
    int maxLen = 1;
    for (int i = 0; i < mat.getHeight(); i++){
        for (int j = 0; j < mat.getWidth(); j++){
            allVal[i][j] = format(mat[i, j]);
            if (allVal[i][j].size() > maxLen) maxLen = allVal[i][j].size();
        }
    }
    maxLen++;
    QString str;
    for (int i = 0; i < mat.getHeight(); i++){
        for (int j = 0; j < mat.getWidth(); j++){
            allVal[i][j].resize(maxLen, ' ');
            str += allVal[i][j];
        }
        if (i != mat.getHeight() - 1) str += '\n';
    }
    return std::make_pair(str, maxLen * mat.getWidth());
}

QString getLiteral(const GenericNumber &num){
    switch(num.getType()){
    case NUMBER:
        return format(num.getDouble());
    case VECTOR:
    {
        const Vector &vec = num.getVector();
        if (vec.dim() <= 3){
            QString str = "";
            for (const double &i : vec){
                str += format(i) + "<br>";
            }
            return str.left(str.size() - 4);
        }
    }
        return "<Vector>";
    case MATRIX:
    {
        const Matrix &mat = num.getMatrix();
        if (mat.getHeight() > 3) return "[Matrix]";
        auto [str, len] = getMatrixStr(mat);
        if (len > 15) return "[Matrix]";
        return str;
    }
    case SPAN_SET:
        return "{Set}";
    case LABEL:
        return QString::fromStdString(num.getLabel());
    case UNKNOWN:
    case EMPTY:
        return "";
    }
}

QString getTooltip(const GenericNumber &num){
    switch(num.getType()){
    case NUMBER:
        return format(num.getDouble());
    case VECTOR:
    {
        const Vector &vec = num.getVector();
        QString str = "<" + format(vec[0]);
        for (int i = 1; i < vec.dim(); i++) str += ", " + format(vec[i]);
        return str + ">";
    }
    case MATRIX:
    case SPAN_SET:
        return getMatrixStr(num.getMatrix()).first;
    case LABEL:
    case UNKNOWN:
    case EMPTY:
        return "";
    }
}

HistoryItem::HistoryItem(const CalculationHistory *item, QWidget *parent)
    : QFrame(parent), ui(new Ui::HistoryItem), itemBase(item)
{
    ui->setupUi(this);
    ui->operandA->setText(getLiteral(item->operandA));
    ui->operandA->setToolTip(getTooltip(item->operandA));
    ui->operandB->setText(getLiteral(item->operandB));
    ui->operandB->setToolTip(getTooltip(item->operandB));
    ui->sign->setText(signs[item->sign].literal);
    ui->result->setText(getLiteral(item->result));
    ui->result->setToolTip(getTooltip(item->result));
}

HistoryItem::~HistoryItem()
{
    delete ui;
}
