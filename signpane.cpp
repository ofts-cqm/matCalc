#include "signpane.h"

SignPane::SignPane(Calculation calc, Evaluator eva, GenericPane *paneA, GenericPane *paneB, GenericPane *paneC) {
    this->currentSign = calc.sign;
    this->evaluator = eva;
    this->operandA = paneA;
    this->operandB = paneB;
    this->resultPane = paneC;
    currentCalc = calc;
}

void SignPane::switchToCalculation(Calculation calc){
    // setup page
    operandA->switchTo(calc.operandA);
    operandB->switchTo(calc.operandB);

    // Todo: show sign

    // evaluate result
    GenericNumber res = evaluator(calc, operandA->getValue(), operandB->getValue());
    resultPane->display(res);
}
