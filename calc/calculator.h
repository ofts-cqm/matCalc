#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "inputmatcher.h"
#include <optional>
#include <sstream>

class Token;

bool radianMode = false;
bool debugMode = false;
double previousAnswer = 0;
InputMatcher input("");
std::ostringstream error_message;
Token *lastToken;

std::optional<double> evaluate(std::string expression, std::string &error_message, bool record_result = false);

Token *matchNext(InputMatcher &input, Token *lastInput);

void logError(std::string error, const InputMatcher &context);

enum class TokenType{
    Number,
    Operator,
    Parenthesis,
    Root
};

void init();

#endif // CALCULATOR_H
