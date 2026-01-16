#ifndef PARENTHESISTOKEN_H
#define PARENTHESISTOKEN_H

#include "token.h"
#include "roottoken.h"

class ParenthesisToken : public Token
{
public:
    ParenthesisToken(RootToken &content, Token *parent);

    virtual double evaluate() const override;

    virtual bool parse(InputMatcher &input, Token *lastInput) const override;

    virtual void debug() const override;

    virtual Calculator::TokenType type() const override;

    RootToken content;
};

#endif // PARENTHESISTOKEN_H
