#include "historyitem.h"
#include "history/ui_historyitem.h"
#include "../panes/genericpane.h"
#include "../util.h"
#include "../mainwindow.h"

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
        return "\n" + format(num.getDouble()) + "\n";
    case VECTOR:
    {
        const Vector &vec = num.getVector();
        if (vec.dim() <= 3){
            QString str = "";
            for (int i = 0; i < vec.dim() - 1; i++){
                str += format(vec[i]) + "\n";
            }
            return str + format(vec[vec.dim() - 1]);
        }
    }
        return "\n<Vector>\n";
    case MATRIX:
    {
        const Matrix &mat = num.getMatrix();
        if (mat.getHeight() > 3) return "\n[Matrix]\n";
        auto [str, len] = getMatrixStr(mat);
        if (len > 15) return "\n[Matrix]\n";
        return str;
    }
    case SPAN_SET:
        return "\n{Set}\n";
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
    : QFrame(parent), ui(new Ui::HistoryItem), itemBase(*item), calcBase(item->getCalculation())
{
    ui->setupUi(this);
    ui->operandA->setText(getLiteral(item->operandA));
    ui->operandA->setToolTip(getTooltip(item->operandA));
    ui->operandB->setText(getLiteral(item->operandB));
    ui->operandB->setToolTip(getTooltip(item->operandB));
    ui->sign->setText(signs[item->sign].literal);
    if (ui->sign->text().trimmed().isEmpty()) ui->sign->setText(" . ");
    if (item->sign == EQU) ui->sign->hide();
    ui->result->setText(getLiteral(item->result));
    ui->result->setToolTip(getTooltip(item->result));

    if (!item->operandA.hasValue()) ui->operandA->hide();
    if (!item->operandB.hasValue()) ui->operandB->hide();
    if (!item->result.hasValue()) ui->result->hide();

    connect(ui->operandA, &QPushButton::clicked, this, &HistoryItem::op1Pressed);
    connect(ui->operandB, &QPushButton::clicked, this, &HistoryItem::op2Pressed);
    connect(ui->result, &QPushButton::clicked, this, &HistoryItem::op3Pressed);
}

HistoryItem::~HistoryItem()
{
    delete ui;
    delete calcBase;
}

void HistoryItem::mousePressEvent(QMouseEvent *event){
    if (itemBase.page == Page::CALCULATOR){
        EvaluationPage::restore(QString::fromStdString(itemBase.operandA.getLabel()));
        return;
    }
    MainWindow::setPage(itemBase.page)->restore(*this);
}

void HistoryItem::op1Pressed() { GenericPane::setClipBoard(itemBase.operandA); }
void HistoryItem::op2Pressed() { GenericPane::setClipBoard(itemBase.operandB); }
void HistoryItem::op3Pressed() { GenericPane::setClipBoard(itemBase.result); }
