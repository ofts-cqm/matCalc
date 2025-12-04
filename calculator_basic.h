#ifndef CALCULATOR_BASIC_H
#define CALCULATOR_BASIC_H

#include "genericnumber.h"
#include <QtCore/qobject.h>
enum Sign{
    PLUS,
    MINUS,
    MUL,
    DOT,
    CROSS,
    PROJ,
    PERP,
    LENGTH,
    RREF,
    INVT,
    TRANS,
    NULL_SPACE,
    COL_SPACE,
    RANK,
    BASE,
    SOLVE
};

struct SignDefinition{
    SignDefinition(Sign sign, QString literal, bool isFunction = false, bool isExponent = false, bool isAbs = false){
        this->sign = sign;
        this->literal = literal;
        this->isExponent = isExponent;
        this->isAbs = isAbs;
        this->isFunction = isFunction;
    }

    QString literal;
    Sign sign;
    bool isFunction;
    bool isAbs;
    bool isExponent;
};

const SignDefinition signs[16] = {
    { PLUS, " + " },
    { MINUS, " - "},
    { MUL, "" },
    { DOT, " . "},
    { CROSS, " X "},
    { PROJ, "Proj", true },
    { PERP, "Perp", true },
    { LENGTH, "", false, false, true },
    { RREF, "RREF", true },
    { INVT, "-1", false, true },
    { TRANS, "T", false, true },
    { NULL_SPACE, "Null", false, true },
    { COL_SPACE, "Col", false, true },
    { RANK, "Rank", false, true },
    { BASE, "Base", false, true },
    { SOLVE, "Solve"}
};

struct Calculation{
    NumberType operandA;
    NumberType operandB;
    NumberType result;
    Sign sign;
};

#endif // CALCULATOR_BASIC_H
