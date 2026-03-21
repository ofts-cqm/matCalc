#include "operatortoken.h"
#include <cmath>
#include "calculator.h"

using namespace Calculator;

OperatorToken::OperatorToken(int precedence, const std::string &operation, const Evaluator evaluator)
    : precedence(precedence), operation(operation), evaluator(evaluator) {}

OperatorToken::OperatorToken(const OperatorToken &tmplt)
    : precedence(tmplt.precedence), operation(tmplt.operation), evaluator(tmplt.evaluator) {}

double OperatorToken::evaluate() const{
    return evaluator(right->evaluate());
}

bool OperatorToken::parse(InputMatcher &input, Token *lastInput) const{
    input.push();
    if (!input.match(operation)){
        input.pop();
        return false;
    }

    if (operation == "-" && (lastInput->type() == TokenType::Number || lastInput->type() == TokenType::Parenthesis)){
        input.pop();
        return false;
    }

    input.ignore();
    return finalizeToken(lastInput, std::make_unique<OperatorToken>(*this));
}

void OperatorToken::debug() const{
    logger.start().write("Unary Operator Token: " + operation, true);
    right->debug();
    logger.finish();
}

TokenType OperatorToken::type() const {return TokenType::Operator; }

static double rtod(double r) {return r * (180.0 / M_PI);}
static double dtor(double d) {return d * (M_PI / 180.0);}

static double angleIn(double ang) {return radianMode ? ang : dtor(ang); }
static double angleOut(double ang) {return radianMode ? ang : rtod(ang); }

static double _cos(double ang){ return cos(angleIn(ang)); }
static double _sin(double ang){ return sin(angleIn(ang)); }
static double _tan(double ang){ return tan(angleIn(ang)); }
static double _sec(double ang){ return 1/_cos(ang);}
static double _csc(double ang){ return 1/_csc(ang);}
static double _cot(double ang){ return 1/_tan(ang);}

static double _acos(double ang){ return angleOut(acos(ang)); }
static double _asin(double ang){ return angleOut(asin(ang)); }
static double _atan(double ang){ return angleOut(atan(ang)); }

void OperatorToken::init(std::vector<Token *> &tokens){
    tokens.append_range(std::vector<OperatorToken *>({
        new OperatorToken(2, "sinh", static_cast<double(*)(double)>(std::sinh)),
        new OperatorToken(2, "cosh", static_cast<double(*)(double)>(std::cosh)),
        new OperatorToken(2, "tanh", static_cast<double(*)(double)>(std::tanh)),
        new OperatorToken(2, "asinh", static_cast<double(*)(double)>(std::asinh)),
        new OperatorToken(2, "acosh", static_cast<double(*)(double)>(std::acosh)),
        new OperatorToken(2, "atanh", static_cast<double(*)(double)>(std::atanh)),
        new OperatorToken(2, "arcsinh", static_cast<double(*)(double)>(std::asinh)),
        new OperatorToken(2, "arccosh", static_cast<double(*)(double)>(std::acosh)),
        new OperatorToken(2, "arctanh", static_cast<double(*)(double)>(std::atanh)),
        new OperatorToken(2, "sin", _sin),
        new OperatorToken(2, "cos", _cos),
        new OperatorToken(2, "tan", _tan),
        new OperatorToken(2, "sec", _sec),
        new OperatorToken(2, "csc", _csc),
        new OperatorToken(2, "cot", _cot),
        new OperatorToken(2, "asin", _asin),
        new OperatorToken(2, "acos", _acos),
        new OperatorToken(2, "atan", _atan),
        new OperatorToken(2, "arcsin", _asin),
        new OperatorToken(2, "arccos", _acos),
        new OperatorToken(2, "arctan", _atan),
        new OperatorToken(2, "log", static_cast<double(*)(double)>(std::log10)),
        new OperatorToken(2, "log2", static_cast<double(*)(double)>(std::log2)),
        new OperatorToken(2, "ln", static_cast<double(*)(double)>(std::log)),
        new OperatorToken(2, "abs", static_cast<double(*)(double)>(std::abs)),
        new OperatorToken(1, "sqrt", static_cast<double(*)(double)>(std::sqrt)),
        new OperatorToken(1, "cbrt", static_cast<double(*)(double)>(std::cbrt)),
        new OperatorToken(0, "-", [](double d){return -d;})
    }));
}
