#ifndef TOKEN_H
#define TOKEN_H

#include "calculator.h"
#include "inputmatcher.h"
#include "logger.h"
#include <memory>

class OperatorToken;

class BinaryOperatorToken;

class ParenthesisToken;

class NumberToken;

class RootToken;

class Token
{
public:
    Token(OperatorToken *parent);

    Token() = default;

    virtual ~Token() = default;

    virtual double evaluate() const = 0;

    virtual bool parse(InputMatcher &input, Token *lastInput) const = 0;

    virtual void debug() const = 0;

    virtual Calculator::TokenType type() const = 0;

    OperatorToken *parent = nullptr;

    static Logger logger;
};

bool finalizeToken(Token *lastInput, std::unique_ptr<Token> &&generated);

#endif // TOKEN_H
