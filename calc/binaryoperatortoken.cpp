#include "binaryoperatortoken.h"
#include <cmath>

BinaryOperatorToken::BinaryOperatorToken(std::unique_ptr<Token> &&left, const BinaryOperatorToken &tmplt)
    : OperatorToken(tmplt), left(std::move(left)), sign(tmplt.sign) {
    this->left->parent = this;
}

BinaryOperatorToken::BinaryOperatorToken(int precedence, const std::string &operation, Sign sign)
    : OperatorToken(precedence, operation, [](double d){return d;}), sign(sign){}

double BinaryOperatorToken::evaluate() const{
    double a = left->evaluate(), b = right->evaluate();
    switch (sign){
    case Sign::ADD:
        return a + b;
    case Sign::SUB:
        return a - b;
    case Sign::MUL:
        return a * b;
    case Sign::DIV:
        return a / b;
    case Sign::EXP:
        return pow(a, b);
    }
}

bool BinaryOperatorToken::parse(InputMatcher &input, Token *lastInput) const{
    if (!input.match(operation)) return false;
    if (lastInput->type() != TokenType::Number && lastInput->type() != TokenType::Parenthesis){
        logError("Error: Left Operand For Binary Operator Token is Neither Number Nor A Parenthesis", input);
        return false;
    }

    input.push();
    OperatorToken *currentToken = lastInput->parent;

    while (currentToken->precedence <= this->precedence) currentToken = currentToken->parent;

    currentToken->right = std::make_unique<BinaryOperatorToken>(std::move(currentToken->right), *this);
    currentToken->right->parent = currentToken;
    lastToken = currentToken->right.get();
    input.ignore();
    return true;
}

void BinaryOperatorToken::debug() const {
    logger.start().write("BinaryOperatorToken " + operation, true);
    logger.start().write("Left: ");
    left->debug();
    logger.write("Right: ", true);
    right->debug();
    logger.finish().finish();
}

BinaryOperatorToken *BinaryOperatorToken::multiply = nullptr;

double add(double a, double b) {return a + b;}

void BinaryOperatorToken::init(std::vector<Token *> &tokens){
    tokens.append_range(std::vector<OperatorToken *>({
        new BinaryOperatorToken(4, "+", Sign::ADD),
        new BinaryOperatorToken(4, "-", Sign::SUB),
        multiply = new BinaryOperatorToken(3, "*", Sign::MUL),
        new BinaryOperatorToken(3, "/", Sign::DIV),
        new BinaryOperatorToken(1, "^", Sign::EXP)
    }));
}
