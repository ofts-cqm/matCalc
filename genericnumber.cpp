#include "genericnumber.h"
#include "numbers/spanset.h"
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

GenericNumber::GenericNumber(const Matrix *mat){
    this->type = MATRIX;
    this->num.mat = mat;
}

GenericNumber::GenericNumber(const std::string *str){
    this->type = LABEL;
    this->num.lab = str;
}

GenericNumber::GenericNumber(const SpanSet *set){
    this->type = SPAN_SET;
    this->num.set = set;
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

const Matrix &GenericNumber::getMatrix() const {
    assert(this->type == MATRIX);
    return *num.mat;
}

const std::string &GenericNumber::getLabel() const {
    assert(this->type == LABEL);
    return *num.lab;
}

const SpanSet &GenericNumber::getSpanSet() const {
    assert(this->type == SPAN_SET);
    return *num.set;
}

GenericNumber GenericNumber::deepclone() const{
    GenericNumber number;
    number.type = this->type;

    switch (this->type){

    case NUMBER:
        number.num.num = new double {this->getDouble()};
        break;
    case VECTOR:
        number.num.vec = new Vector(this->getVector());
        break;
    case MATRIX:
        number.num.mat = new Matrix(this->getMatrix());
        break;
    case LABEL:
        number.num.lab = &this->getLabel();
        break;
    case SPAN_SET:
        number.num.set = new SpanSet(this->getSpanSet());
        break;
    case UNKNOWN:
    case EMPTY:
        break;
    }

    return number;
}
