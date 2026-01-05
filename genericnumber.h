#ifndef GENERICNUMBER_H
#define GENERICNUMBER_H

#include "matrix.h"
#include "vector.h"

union NumberHolder {
    const double *num;
    const Vector *vec;
    const Matrix *mat;
    const SpanSet *set;
    const std::string *lab;

    ~NumberHolder(){};
};

enum NumberType{
    NUMBER,
    VECTOR,
    MATRIX,
    SPAN_SET,
    LABEL,
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
    GenericNumber(const std::string *);
    GenericNumber(const SpanSet *);

    NumberType getType() const;
    const double &getDouble() const;
    const Vector &getVector() const;
    const Matrix &getMatrix() const;
    const SpanSet &getSpanSet() const;
    const std::string &getLabel() const;

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
