#include "abstractpage.h"
#include <QtWidgets/qboxlayout.h>

AbstractPage::AbstractPage(Evaluator evaluator, Calculation defaultCalculation, QWidget *parent)
    : QWidget(parent){
    this->evaluator = evaluator;
    this->currentCalculation = defaultCalculation;
    this->sign = new SignPane(defaultCalculation.sign, this);

    QVBoxLayout *main = new QVBoxLayout(this);
    this->setLayout(main);

    this->control = new QHBoxLayout(this);
    main->addLayout(control);

    this->content = new QHBoxLayout(this);
    main->addLayout(content);
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
    this->operandA->switchTo(currentCalculation.operandA);
    this->operandB->switchTo(currentCalculation.operandB);
    evaluate();
}

void AbstractPage::evaluate(){
    GenericNumber number = evaluator(currentCalculation, operandA->getValue(), operandB->getValue());
    resultPane->display(number);
}
