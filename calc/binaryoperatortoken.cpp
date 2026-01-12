#include "binaryoperatortoken.h"
#include <cmath>

BinaryOperatorToken::BinaryOperatorToken(Token *left, const BinaryOperatorToken &tmplt)
    : OperatorToken(tmplt), left(left), evaluator(tmplt.evaluator) {
    left->parent = this;
}

BinaryOperatorToken::BinaryOperatorToken(int precedence, const std::string &operation, const BinaryEvaluator &evaluator)
    : OperatorToken(precedence, operation, [](double d){return d;}), evaluator(evaluator){}

BinaryOperatorToken::~BinaryOperatorToken(){
    delete left;
}

double BinaryOperatorToken::evaluate() const{
    return evaluator(left->evaluate(), right->evaluate());
}

Token *BinaryOperatorToken::parse(InputMatcher &input, Token *lastInput) const{
    if (!input.match(operation)) return nullptr;
    if (lastInput->type() != TokenType::Number && lastInput->type() != TokenType::Parenthesis){
        logError("Error: Left Operand For Binary Operator Token is Neither Number Nor A Parenthesis", input);
        return nullptr;
    }

    input.push();
    OperatorToken *currentToken = lastInput->parent;

    while (currentToken->precedence > this->precedence) currentToken = currentToken->parent;

    BinaryOperatorToken *newtok = new BinaryOperatorToken(currentToken->right, *this);
    newtok->parent = currentToken;
    currentToken->right = newtok;

    newtok->right = matchNext(input, newtok);
    if (newtok->right == nullptr){
        input.pop();
        logError("Error: Missing Left Operand For Binary Operator Token", input);
        return nullptr;
    }

    input.ignore();
    return newtok;
}

void BinaryOperatorToken::debug() const {
    logger.start().write("BinaryOperatorToken " + operation, true);
    logger.start().write("Left: ");
    left->debug();
    logger.write("Right: ");
    right->debug();
    logger.finish().finish();
}

void BinaryOperatorToken::init(std::vector<Token *> &tokens){
    tokens.append_range(std::vector<OperatorToken *>({
        new BinaryOperatorToken(4, "+", [](double a, double b){ return a + b; }),
        new BinaryOperatorToken(4, "-", [](double a, double b){ return a - b; }),
        multiply = new BinaryOperatorToken(4, "*", [](double a, double b){ return a * b; }),
        new BinaryOperatorToken(4, "/", [](double a, double b){ return a / b; }),
        new BinaryOperatorToken(4, "^", pow<double>)
    }));
}
