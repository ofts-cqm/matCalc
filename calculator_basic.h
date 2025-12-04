#ifndef CALCULATOR_BASIC_H
#define CALCULATOR_BASIC_H

#include "genericnumber.h"
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

struct Calculation{
    NumberType operandA;
    NumberType operandB;
    NumberType result;
    Sign sign;
};

#endif // CALCULATOR_BASIC_H
