#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <optional>

bool radianMode = false;
bool debugMode = false;
double previousAnswer = 0;

std::optional<double> evaluate();

#endif // CALCULATOR_H
