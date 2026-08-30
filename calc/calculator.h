#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "inputmatcher.h"
#include <optional>

class Token;

namespace Calculator{

    extern bool radianMode;
    extern bool debugMode;
    extern double previousAnswer;
    extern InputMatcher input;
    extern Token *lastToken;

    std::optional<double> evaluate(std::string expression, bool record_result = false);

    bool matchNext(InputMatcher &input, Token *lastInput);

    void logError(std::string error, const InputMatcher &context);

    std::string getShortErrorMessage();

    std::string getLongErrorMessage();

    enum class TokenType{
        Number,
        Operator,
        Parenthesis,
        Root
    };

    void init();
}

#endif // CALCULATOR_H
