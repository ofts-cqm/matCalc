#include "binaryoperatortoken.h"
#include <cmath>

using namespace Calculator;

BinaryOperatorToken::BinaryOperatorToken(std::unique_ptr<Token> &&left, const BinaryOperatorToken &tmplt)
    : OperatorToken(tmplt), left(std::move(left)), sign(tmplt.sign) {
    this->left->parent = this;
}

BinaryOperatorToken::BinaryOperatorToken(const int precedence, const std::string &operation, const Sign sign)
    : OperatorToken(precedence, operation, [](const double d){return d;}), sign(sign){}

double BinaryOperatorToken::evaluate() const{
    const double a { left->evaluate() };
    const double b { right->evaluate() };
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
    return 0;
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

void BinaryOperatorToken::init(std::vector<std::unique_ptr<Token>> &tokens){
    auto add = [&tokens](int precedence, const std::string &operation, Sign sign) {
        auto token = std::unique_ptr<BinaryOperatorToken>(new BinaryOperatorToken(precedence, operation, sign));
        BinaryOperatorToken *observer = token.get();
        tokens.push_back(std::move(token));
        return observer;
    };
    add(4, "+", Sign::ADD);
    add(4, "-", Sign::SUB);
    multiply = add(3, "*", Sign::MUL);
    add(3, "/", Sign::DIV);
    add(1, "^", Sign::EXP);
}
