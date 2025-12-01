#ifndef GENERICNUMBER_H
#define GENERICNUMBER_H

#include "vector.h"

union NumberHolder {
    const double *num;
    const Vector *vec;

    ~NumberHolder(){};
};

enum NumberType{
    NUMBER,
    VECTOR,
    UNKNOWN
};

class GenericNumber
{
public:
    GenericNumber();
    GenericNumber(const double &);
    GenericNumber(const Vector &);

    NumberType getType();
    const double &getDouble();
    const Vector &getVector();


private:
    NumberType type;
    NumberHolder num;
};

#endif // GENERICNUMBER_H
