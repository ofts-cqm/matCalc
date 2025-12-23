#ifndef GENERICNUMBER_H
#define GENERICNUMBER_H

#include "matrix.h"
#include "vector.h"

union NumberHolder {
    const double *num;
    const Vector *vec;
    const Matrix *mat;

    ~NumberHolder(){};
};

enum NumberType{
    NUMBER,
    VECTOR,
    MATRIX,
    UNKNOWN,
    EMPTY
};

#define NUMBER_TYPE_COUNT 5

class GenericNumber
{
public:
    GenericNumber();
    GenericNumber(const double *);
    GenericNumber(const Vector *);
    GenericNumber(const Matrix *);

    NumberType getType() const;
    const double &getDouble() const;
    const Vector &getVector() const;
    const Matrix &getMatrix() const;

    const GenericNumber &operator=(const GenericNumber &src) {
        this->type = src.type;
        this->num = src.num;
        return *this;
    }

    GenericNumber deepclone() const;

    static const GenericNumber unknown;

private:
    NumberType type;
    NumberHolder num;
};

#endif // GENERICNUMBER_H
