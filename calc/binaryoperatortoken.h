#ifndef BINARYOPERATORTOKEN_H
#define BINARYOPERATORTOKEN_H

#include "operatortoken.h"
#include <memory>

class BinaryOperatorToken : public OperatorToken
{
public:
    BinaryOperatorToken(std::unique_ptr<Token> &&left, const BinaryOperatorToken &tmplt);

    virtual double evaluate() const override;

    virtual bool parse(InputMatcher &input, Token *lastInput) const override;

    virtual void debug() const override;

    std::unique_ptr<Token> left;

    const Sign sign;

    static void init(std::vector<Token *> &tokens);

    static BinaryOperatorToken *multiply;

protected:
    BinaryOperatorToken(int precedence, const std::string &operation, Sign sign);
};

#endif // BINARYOPERATORTOKEN_H
