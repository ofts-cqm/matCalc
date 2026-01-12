#ifndef BINARYOPERATORTOKEN_H
#define BINARYOPERATORTOKEN_H

#include "operatortoken.h"

class BinaryOperatorToken : public OperatorToken
{
public:
    using BinaryEvaluator = std::function<double(double, double)>;

    BinaryOperatorToken(Token *left, const BinaryOperatorToken &tmplt);

    virtual ~BinaryOperatorToken();

    virtual double evaluate() const override;

    virtual Token *parse(InputMatcher &input, Token *lastInput) const override;

    virtual void debug() const override;

    Token *left;

    const BinaryEvaluator &evaluator;

    static void init(std::vector<Token *> &tokens);

    static BinaryOperatorToken *multiply;

protected:
    BinaryOperatorToken(int precedence, const std::string &operation, const BinaryEvaluator &evaluator);
};

#endif // BINARYOPERATORTOKEN_H
