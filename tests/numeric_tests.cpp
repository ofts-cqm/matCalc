#include "dimensionmismatchexception.h"
#include "numbers/polynomial.h"
#include "numbers/sturm.h"
#include "numbers/vector.h"

#include <QString>
#include <cmath>
#include <iostream>
#include <stdexcept>

bool isZero(double value) {
    return std::abs(value) < 1e-9;
}

void throwRangeException(int accessed, int maximum) {
    throw std::out_of_range("Invalid index " + std::to_string(accessed) +
                            " for length " + std::to_string(maximum));
}

QString format(double value) {
    return QString::number(value);
}

int main() {
    bool success = true;

    const Vector extended = Vector({1.0, 2.0}).append(3.0);
    success &= extended.dim() == 3 && extended[2] == 3.0;

    try {
        static_cast<void>(Vector(2) + Vector(3));
        success = false;
    } catch (const DimensionMismatchException &) {
    }

    try {
        static_cast<void>(extended[-1]);
        success = false;
    } catch (const std::out_of_range &) {
    }

    try {
        static_cast<void>(Vector(-1));
        success = false;
    } catch (const std::invalid_argument &) {
    }

    const std::set<double> roots = Sturm(Polynomial({-0.25, 0.0, 1.0})).roots();
    success &= roots.size() == 2;
    if (roots.size() == 2) {
        auto root = roots.begin();
        success &= std::abs(*root++ + 0.5) < 1e-7;
        success &= std::abs(*root - 0.5) < 1e-7;
    }
    success &= Sturm(Polynomial({4.0})).roots().empty();

    if (!success) std::cerr << "Numeric reliability checks failed\n";
    return success ? 0 : 1;
}
