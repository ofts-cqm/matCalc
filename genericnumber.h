#ifndef GENERICNUMBER_H
#define GENERICNUMBER_H

#include "numbers/matrix.h"
#include "numbers/spanset.h"
#include "numbers/vector.h"
#include <QtCore/qobject.h>
#include <variant>

enum NumberType{
    NUMBER,
    VECTOR,
    MATRIX,
    SPAN_SET,
    LABEL,
    UNKNOWN,
    EMPTY
};

#define NUMBER_TYPE_COUNT 7

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

    GenericNumber(double &&);
    GenericNumber(Vector &&);
    GenericNumber(Matrix &&);
    GenericNumber(std::string &&);
    GenericNumber(SpanSet &&);

    explicit GenericNumber(const QJsonObject &cache);

    NumberType getType() const;
    const double &getDouble() const;
    const Vector &getVector() const;
    const Matrix &getMatrix() const;
    const SpanSet &getSpanSet() const;
    const std::string &getLabel() const;

    const GenericNumber &operator=(const GenericNumber &src);

    QJsonObject toJson() const;

    static const GenericNumber unknown;

    //friend NumberHolder;

private:
    NumberType type;
    std::variant<double, Vector, Matrix, std::string, SpanSet> num;
};

#endif // GENERICNUMBER_H
