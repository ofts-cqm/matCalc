#include "genericnumber.h"
#include "numbers/spanset.h"
#include <cassert>

const GenericNumber GenericNumber::unknown = GenericNumber();

GenericNumber::GenericNumber()
    : type(UNKNOWN) {}

GenericNumber::GenericNumber(const GenericNumber &other)
    : type(other.getType()), num(other.num){}

GenericNumber::GenericNumber(GenericNumber &&other)
    : type(other.getType()), num(std::move(other.num)){}

GenericNumber::GenericNumber(const double &num)
    : num(num), type(NUMBER) {}

GenericNumber::GenericNumber(const Vector &num)
    : num(num), type(VECTOR) {}

GenericNumber::GenericNumber(const Matrix &num)
    : num(num), type(MATRIX) {}

GenericNumber::GenericNumber(const std::string &num)
    : num(num), type(LABEL) {}

GenericNumber::GenericNumber(const SpanSet &num)
    : num(num), type(SPAN_SET) {}

GenericNumber::GenericNumber(double &&num)
    : num(std::move(num)), type(NUMBER) {}

GenericNumber::GenericNumber(Vector &&num)
    : num(std::move(num)), type(VECTOR) {}

GenericNumber::GenericNumber(Matrix &&num)
    : num(std::move(num)), type(MATRIX) {}

GenericNumber::GenericNumber(std::string &&num)
    : num(std::move(num)), type(LABEL) {}

GenericNumber::GenericNumber(SpanSet &&num)
    : num(std::move(num)), type(SPAN_SET) {}

NumberType GenericNumber::getType() const {
    return this->type;
}

const double &GenericNumber::getDouble() const {
    assert(this->type == NUMBER);
    return std::get<double>(num);
}

const Vector &GenericNumber::getVector() const {
    assert(this->type == VECTOR);
    return std::get<Vector>(num);
}

const Matrix &GenericNumber::getMatrix() const {
    assert(this->type == MATRIX);
    return std::get<Matrix>(num);
}

const std::string &GenericNumber::getLabel() const {
    assert(this->type == LABEL);
    return std::get<std::string>(num);
}

const SpanSet &GenericNumber::getSpanSet() const {
    assert(this->type == SPAN_SET);
    return std::get<SpanSet>(num);
}

const GenericNumber &GenericNumber::operator=(const GenericNumber &src){
    this->type = src.getType();
    this->num = src.num;
    return *this;
}
