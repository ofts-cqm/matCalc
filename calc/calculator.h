#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "inputmatcher.h"
#include <optional>
#include <sstream>

class Token;

namespace Calculator{

    extern bool radianMode;
    extern bool debugMode;
    extern double previousAnswer;
    extern InputMatcher input;
    static std::ostringstream error_message;
    static std::string first_error;
    static int errorCount;
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
