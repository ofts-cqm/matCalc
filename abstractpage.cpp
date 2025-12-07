#include "abstractpage.h"
#include "util.h"
#include <QtWidgets/qboxlayout.h>

AbstractPage::AbstractPage(Evaluator evaluator, Calculation defaultCalculation, QWidget *parent)
    : QWidget(parent){
    this->evaluator = evaluator;
    this->sign = new SignPane(defaultCalculation.sign, this);

    QVBoxLayout *main = new QVBoxLayout(this);
    this->setLayout(main);

    main->addItem(getVerticalSpacer());
    QHBoxLayout *controlLayout = new QHBoxLayout();
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

void AbstractPage::switchTo(Calculation nextCalculation){
    currentCalculation = nextCalculation;
    this->sign->display(currentCalculation.sign);
    if (this->operandA != nullptr) {
        this->operandA->switchTo(currentCalculation.operandA);
        this->operandA->applyBorder(signs[nextCalculation.sign]);
    }
    if (this->operandB != nullptr) {
        this->operandB->switchTo(currentCalculation.operandB);
        this->operandB->applyBorder(signs[nextCalculation.sign]);
    }
    evaluate();
}

void AbstractPage::evaluate(){
    /*GenericNumber *number = evaluator(
        currentCalculation,
        operandA == nullptr ? &GenericNumber::unknown : &operandA->getValue(),
        operandB == nullptr ? &GenericNumber::unknown : &operandB->getValue());
    resultPane->display(*number);*/
}
