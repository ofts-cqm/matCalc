#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H

#include "token.h"

class NumberToken: public Token
{
public:
    NumberToken();

    NumberToken(double val, OperatorToken *lastInput = nullptr);

    virtual ~NumberToken();

    virtual double evaluate() const;

    virtual Token *parse(InputMatcher &input, Token *lastInput) const;

    virtual void debug() const;

    virtual TokenType type() const;

    double val;
};

#endif // NUMBERTOKEN_H
