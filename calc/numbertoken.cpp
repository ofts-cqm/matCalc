#include "numbertoken.h"
#include "operatortoken.h"
#include <cmath>
#include <numbers>

long matchNum(InputMatcher &input, int start);

int getNextDigit(InputMatcher input);

NumberToken::NumberToken():Token() {}

NumberToken::NumberToken(double val, OperatorToken *lastToken): Token(lastToken), val(val) {}

NumberToken::~NumberToken(){};

double NumberToken::evaluate() const {return val;}

Token *NumberToken::parse(InputMatcher &input, Token *lastInput) const {
    if (input.match("E", false)) return finalizeToken(lastInput, lastToken = new NumberToken(std::numbers::e));
    if (input.match("PI", false) || input.match("π")) return finalizeToken(lastInput, lastToken = new NumberToken(std::numbers::pi));
    if (input.match("ANS", false)) return finalizeToken(lastInput, lastToken = new NumberToken(previousAnswer));

    if (lastInput->type() != TokenType::Operator){
        logError("Error: Cannot Process Numbers Without Prior Operator", input);
    }

    input.push();

    int digit = getNextDigit(input);
    if (digit == -1) {
        input.pop();
        return nullptr;
    }
    long number = matchNum(input, digit);

    if (input.match(".")) {
        digit = getNextDigit(input);
        if (digit != -1) {
            long decimal = matchNum(input, digit);
            double fp = decimal / pow(10, std::to_string(decimal).size());
            input.ignore();
            return lastToken = new NumberToken(number + fp, dynamic_cast<OperatorToken *>(lastInput));
        }
    }

    input.ignore();
    input.push();

    if (input.match("e", false)) {
        bool flip = input.match("-");
        digit = getNextDigit(input);
        if (digit != -1) {
            long exponent = matchNum(input, digit);
            if (flip) exponent *= -1;
            input.ignore();
            return lastToken = new NumberToken(number * pow(10, exponent), dynamic_cast<OperatorToken *>(lastInput));
        }

        input.pop();
        return lastToken = new NumberToken(number);
    }

    input.ignore();
    return lastToken = new NumberToken(number, dynamic_cast<OperatorToken *>(lastInput));
}

void NumberToken::debug() const{
    logger.start().write("Number Token: " + std::to_string(val), true).finish();
}

TokenType NumberToken::type() const {return TokenType::Number; }

int getNextDigit(InputMatcher input) {
    std::string_view tmp = input.get(1);
    if (tmp == "") return -1;
    int c = tmp[0] - '0';
    if (c >= 0 && c <= 9) {
        input.skip(1);
        return c;
    }
    return -1;
}

long matchNum(InputMatcher input, int start) {
    long number = 0;
    while (start != -1) {
        number *= 10;
        number += start;
        start = getNextDigit(input);
    }
    return number;
}
