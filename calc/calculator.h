#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "inputmatcher.h"
#include <optional>
#include <sstream>

class Token;

extern bool radianMode;
extern bool debugMode;
extern double previousAnswer;
extern InputMatcher input;
static std::ostringstream error_message;
extern Token *lastToken;

std::optional<double> evaluate(std::string expression, std::string &error_message, bool record_result = false);

bool matchNext(InputMatcher &input, Token *lastInput);

void logError(std::string error, const InputMatcher &context);

enum class TokenType{
    Number,
    Operator,
    Parenthesis,
    Root
};

void init();

#endif // CALCULATOR_H
