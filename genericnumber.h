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
    UNKNOWN,
    EMPTY
};

class GenericNumber
{
public:
    GenericNumber();
    GenericNumber(const double &);
    GenericNumber(const Vector *);

    NumberType getType() const;
    const double &getDouble() const;
    const Vector &getVector() const;

    const GenericNumber &operator=(const GenericNumber &src) {
        this->type = src.type;
        this->num = src.num;
        return *this;
    }

    static const GenericNumber unknown;

private:
    NumberType type;
    NumberHolder num;
};

#endif // GENERICNUMBER_H
