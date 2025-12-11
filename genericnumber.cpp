#include "genericnumber.h"
#include <cassert>

GenericNumber::GenericNumber(){
    this->type = UNKNOWN;
}

GenericNumber::GenericNumber(const double *num) {
    this->type = NUMBER;
    this->num.num = num;
}

GenericNumber::GenericNumber(const Vector *vec){
    this->type = VECTOR;
    this->num.vec = vec;
}

const GenericNumber GenericNumber::unknown = GenericNumber();

NumberType GenericNumber::getType() const {
    return this->type;
}

const double &GenericNumber::getDouble() const {
    assert(this->type == NUMBER);
    return *num.num;
}

const Vector &GenericNumber::getVector() const {
    assert(this->type == VECTOR);
    return *num.vec;
}
