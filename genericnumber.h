#ifndef GENERICNUMBER_H
#define GENERICNUMBER_H

#include "numbers/matrix.h"
#include "numbers/spanset.h"
#include "numbers/vector.h"
#include "numbers/eigenspace.h"
#include <QtCore/qobject.h>
#include <variant>

enum NumberType{
    NUMBER,
    VECTOR,
    MATRIX,
    SPAN_SET,
    LABEL,
    EIGEN,
    UNKNOWN,
    EMPTY
};

#define NUMBER_TYPE_COUNT 8

class GenericNumber
{
public:
    GenericNumber();

    GenericNumber(const GenericNumber &);

    GenericNumber(GenericNumber &&other);

    GenericNumber(const double &);
    GenericNumber(const Vector &);
    GenericNumber(const Matrix &);
    GenericNumber(const std::string &);
    GenericNumber(const SpanSet &);
    GenericNumber(const EigenSpace &);

    GenericNumber(double &&);
    GenericNumber(Vector &&);
    GenericNumber(Matrix &&);
    GenericNumber(std::string &&);
    GenericNumber(SpanSet &&);
    GenericNumber(EigenSpace &&);

    explicit GenericNumber(const QJsonObject &cache);

    NumberType getType() const;
    const double &getDouble() const;
    const Vector &getVector() const;
    const Matrix &getMatrix() const;
    const SpanSet &getSpanSet() const;
    const std::string &getLabel() const;
    const EigenSpace &getEigen() const;

    bool hasValue() const;

    const GenericNumber &operator=(const GenericNumber &src);

    QJsonObject toJson() const;

    static const GenericNumber unknown;

    //friend NumberHolder;

private:
    NumberType type;
    std::variant<double, Vector, Matrix, std::string, SpanSet, EigenSpace> num;
};

#endif // GENERICNUMBER_H
