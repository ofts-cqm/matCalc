#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H

#include "token.h"

class NumberToken: public Token
{
public:
    NumberToken();

    NumberToken(double val, OperatorToken *lastInput = nullptr);

    virtual double evaluate() const;

    virtual bool parse(InputMatcher &input, Token *lastInput) const;

    virtual void debug() const;

    virtual TokenType type() const;

    double val;
};

#endif // NUMBERTOKEN_H
