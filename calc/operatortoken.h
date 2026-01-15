#ifndef OPERATORTOKEN_H
#define OPERATORTOKEN_H

#include "token.h"
#include <functional>
#include <memory>
class OperatorToken : public Token
{
public:
    using Evaluator = std::function<double(double)>;

    OperatorToken(const OperatorToken &tmplt);

    virtual double evaluate() const;

    virtual bool parse(InputMatcher &input, Token *lastInput) const;

    virtual void debug() const;

    virtual TokenType type() const;

    std::unique_ptr<Token> right;

    const int precedence;

    const std::string operation;

    const Evaluator evaluator;

    static void init(std::vector<Token *> &tokens);

protected:
    OperatorToken(int precedence, const std::string &operation, const Evaluator evaluator);
};

enum class Sign{
    ADD,
    SUB,
    MUL,
    DIV,
    EXP
};

#endif // OPERATORTOKEN_H
