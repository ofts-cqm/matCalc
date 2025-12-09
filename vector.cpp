#include "vector.h"
#include "dimensionmismatchexception.h"
#include <cmath>

Vector::Vector(): std::vector<double>() {}

//Vector::Vector(std::vector<double> source): std::vector<double>(source) {}

Vector::Vector(std::vector<double> source) : Vector(source.size()){
    std::vector<double>::operator=(source);
}

Vector::Vector(int size): std::vector<double>() {
    this->resize(3, 0);
}

Vector::Vector(Vector const& source): Vector((std::vector<double>)source){

}

void Vector::setSize(int size){
    this->resize(size, 0);
}

double &Vector::operator[](int index){
    return std::vector<double>::operator[](index);
}

double Vector::operator[](int index) const{
    return std::vector<double>::operator[](index);
}

Vector &Vector::operator=(const Vector &other){
    std::vector<double>::operator=(other);
    return *this;
}

Vector Vector::operator+(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    Vector newVec(other.dim());

    for (int i = 0; i < this->dim(); i++){
        newVec[i] = (* this)[i] + other[i];
    }

    return newVec;
}

Vector Vector::operator-(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    Vector newVec(other.dim());

    for (int i = 0; i < this->dim(); i++){
        newVec[i] = (* this)[i] - other[i];
    }

    return newVec;
}


double Vector::operator*(const Vector &other) const{
    if (this->dim() != other.dim())
        throw new DimensionMismatchException(this->dim(), other.dim());

    double res = 0;

    for (int i = 0; i < this->dim(); i++){
        res += (* this)[i] * other[i];
    }

    return res;
}

Vector Vector::operator*(double num) const{
    Vector newVec(*this);

    for (int i = 0; i < this->dim(); i++){
        newVec[i] *= num;
    }

    return newVec;
}

Vector Vector::cross(const Vector &other) const{
    if (this->dim() != 3)
        throw new DimensionMismatchException(this->dim(), 3);
    if (other.dim() != 3)
        throw new DimensionMismatchException(other.dim(), 3);

    double a = (* this)[1] * other[2] - (* this)[2] * other[1];
    double b = (* this)[2] * other[0] - (* this)[0] * other[2];
    double c = (* this)[0] * other[1] - (* this)[1] * other[0];

    return Vector({a, b, c});
}

double Vector::norm() const{
    double res = 0;

    for (int i = 0; i < this->dim(); i++){
        res += this[i] * this[i];
    }

    return std::sqrt(res);
}

Vector Vector::unit() const{
    return *this * (1 / this->norm());
}

int Vector::dim() const{
    return this->size();
}
