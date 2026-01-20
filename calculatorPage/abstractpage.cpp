#include "abstractpage.h"
#include "../util.h"
#include "../history/calculationhistory.h"
#include <QtWidgets/qboxlayout.h>

AbstractPage::AbstractPage(Evaluator evaluator, const Calculation *defaultCalculation, History::Page page, QWidget *parent)
    : QWidget(parent), evaluator(evaluator), page(page) {
    this->sign = new SignPane(defaultCalculation->sign, this);
    this->equal = new SignPane(EQU, this);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->setSpacing(0);
    this->setLayout(main);

    main->addItem(getVerticalSpacer());
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->setSpacing(0);
    controlLayout->addSpacerItem(getHorizontalSpacer());
    controlLayout->addWidget(control = new ControlPane(this));
    controlLayout->addSpacerItem(getHorizontalSpacer());
    main->addLayout(controlLayout);

    main->addLayout(content = new QHBoxLayout());
    main->addItem(getVerticalSpacer());
    this->currentCalculation = defaultCalculation;
}

GenericPane *AbstractPage::registerOperand(GenericPane *operand, int position){
    switch (position){
    case 1:
        operandA = operand;
        break;
    case 2:
        operandB = operand;
        break;
    default:
        resultPane = operand;
    }

    return operand;
}

void AbstractPage::switchTo(const Calculation *nextCalculation){
    currentCalculation = nextCalculation;
    this->sign->display(currentCalculation->sign);
    if (this->operandA != nullptr) {
        this->operandA->switchTo(currentCalculation->operandA);
        this->operandA->applyBorder(signs[nextCalculation->sign]);
    }
    if (this->operandB != nullptr) {
        this->operandB->switchTo(currentCalculation->operandB);
        this->operandB->applyBorder(signs[nextCalculation->sign]);
    }
    currentPage = this;
    control->refreshSizer();
    evaluate();
}

void AbstractPage::restore(const HistoryItem &history){
    switchTo(history.calcBase);
    this->operandA->display(history.itemBase.operandA);
    this->operandB->display(history.itemBase.operandB);
    this->resultPane->display(history.itemBase.result);
}

void AbstractPage::evaluate(bool record){
    const GenericNumber *op1 = operandA == nullptr ? &GenericNumber::unknown : operandA->getValue();
    const GenericNumber *op2 = operandB == nullptr ? &GenericNumber::unknown : operandB->getValue();
    GenericNumber *number = evaluator(currentCalculation, op1, op2);
    resultPane->display(*number);
    if (record) History::addHistory(page, currentCalculation->sign, *op1, *op2, *number);
}

AbstractPage *AbstractPage::getCurrent(){
    return currentPage;
}

AbstractPage *AbstractPage::currentPage = nullptr;
