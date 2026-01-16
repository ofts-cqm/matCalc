#include "abstractpage.h"
#include "../util.h"
#include <QtWidgets/qboxlayout.h>

AbstractPage::AbstractPage(Evaluator evaluator, const Calculation *defaultCalculation, QWidget *parent)
    : QWidget(parent), evaluator(evaluator) {
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

AbstractPage::~AbstractPage(){
    clearLayout(this->layout());
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
    evaluate();
}

void AbstractPage::evaluate(){
    GenericNumber *number = evaluator(
        currentCalculation,
        operandA == nullptr ? &GenericNumber::unknown : operandA->getValue(),
        operandB == nullptr ? &GenericNumber::unknown : operandB->getValue());
    resultPane->display(*number);
}

AbstractPage *AbstractPage::getCurrent(){
    return currentPage;
}

AbstractPage *AbstractPage::currentPage = nullptr;
