#include "calc/calculator.h"

#include <cmath>
#include <iostream>
#include <optional>
#include <string>

namespace {
bool expectValue(const std::string &expression, double expected, double tolerance = 1e-9) {
    const std::optional<double> result = Calculator::evaluate(expression);
    if (!result || std::abs(*result - expected) > tolerance) {
        std::cerr << "Expected " << expression << " = " << expected;
        if (result) std::cerr << ", got " << *result;
        std::cerr << "\n" << Calculator::getLongErrorMessage();
        return false;
    }
    return true;
}

bool expectFailure(const std::string &expression) {
    if (Calculator::evaluate(expression).has_value()) {
        std::cerr << "Expected parsing to fail: " << expression << "\n";
        return false;
    }
    return true;
}
}

int main() {
    Calculator::init();
    Calculator::debugMode = false;

    bool success = true;
    success &= expectValue("1+2*3", 7.0);
    success &= expectValue("2(3+1)", 8.0);
    success &= expectValue("csc(30)", 2.0, 1e-8);
    success &= expectFailure("");
    success &= expectFailure("1+");
    success &= expectFailure("(1+2");
    success &= expectFailure("+1");

    for (int i = 0; i < 100; ++i) success &= expectFailure("(1+");
    return success ? 0 : 1;
}
