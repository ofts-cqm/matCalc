#ifndef OPERATORTOKEN_H
#define OPERATORTOKEN_H

#include "token.h"
#include <functional>
class OperatorToken : public Token
{
public:
    using Evaluator = std::function<double(double)>;

    OperatorToken(const OperatorToken &tmplt);

    virtual ~OperatorToken();

    virtual double evaluate() const;

    virtual Token *parse(InputMatcher &input, Token *lastInput) const;

    virtual void debug() const;

    virtual TokenType type() const;

    Token *right;

    const int precedence;

    const std::string &operation;

    const Evaluator &evaluator;

    static void init(std::vector<Token *> &tokens);

protected:
    OperatorToken(int precedence, const std::string &operation, const Evaluator &evaluator);
};

#endif // OPERATORTOKEN_H
