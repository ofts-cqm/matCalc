#include "genericnumber.h"
#include <cassert>

GenericNumber::GenericNumber(){
    this->type = UNKNOWN;
}

GenericNumber::GenericNumber(const double &num) {
    this->type = NUMBER;
    this->num.num = &num;
}

GenericNumber::GenericNumber(const Vector &vec){
    this->type = VECTOR;
    this->num.vec = &vec;
}

NumberType GenericNumber::getType(){
    return this->type;
}

const double &GenericNumber::getDouble(){
    assert(this->type == NUMBER);
    return *num.num;
}

const Vector &GenericNumber::getVector(){
    assert(this->type == VECTOR);
    return *num.vec;
}
