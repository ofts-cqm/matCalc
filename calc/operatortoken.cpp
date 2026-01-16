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
    if (!input.match(operation)) return false;

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
        new OperatorToken(2, "sinh", sinh<double>),
        new OperatorToken(2, "cosh", cosh<double>),
        new OperatorToken(2, "tanh", tanh<double>),
        new OperatorToken(2, "asinh", asinh<double>),
        new OperatorToken(2, "acosh", acosh<double>),
        new OperatorToken(2, "atanh", atanh<double>),
        new OperatorToken(2, "arcsinh", asinh<double>),
        new OperatorToken(2, "arccosh", acosh<double>),
        new OperatorToken(2, "arctanh", atanh<double>),
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
        new OperatorToken(2, "log", log10<double>),
        new OperatorToken(2, "log2", log2<double>),
        new OperatorToken(2, "ln", log<double>),
        new OperatorToken(2, "abs", fabs<double>),
        new OperatorToken(1, "sqrt", sqrt<double>),
        new OperatorToken(1, "cbrt", cbrt<double>),
        new OperatorToken(0, "-", [](double d){return -d;})
    }));
}
