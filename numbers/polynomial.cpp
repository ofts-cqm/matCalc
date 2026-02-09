#include "polynomial.h"
#include "../util.h"
#include <sstream>

Polynomial::Polynomial(): std::vector<double>(1) {}
Polynomial::Polynomial(const Polynomial &src) : std::vector<double>(src){}
Polynomial::Polynomial(Polynomial &&src) : std::vector<double>(src){}
Polynomial::Polynomial(std::initializer_list<double> list) : std::vector<double>(list){}
Polynomial::Polynomial(int length, const Polynomial &src): std::vector<double>(src){
    resize(length);
}

Polynomial Polynomial::operator+(const Polynomial &other) const{
    Polynomial res(std::max(this->size(), other.size()), *this);
    for (int i = 0; i < other.size(); i++){
        res[i] += other[i];
    }

    return res.trim();
}

Polynomial &Polynomial::operator+=(const Polynomial &other){
    if (other.size() > this->size()) this->resize(other.size());
    for (int i = 0; i < other.size(); i++){
        (*this)[i] += other[i];
    }

    return this->trim();
}

Polynomial Polynomial::operator-(const Polynomial &other) const{
    Polynomial res(std::max(this->size(), other.size()), *this);
    for (int i = 0; i < other.size(); i++){
        res[i] -= other[i];
    }

    return res.trim();
}

Polynomial Polynomial::operator-() const{
    Polynomial res = *this;
    for (int i = 0; i < res.size(); i++){
        res[i] *= -1;
    }
    return res;
}

Polynomial Polynomial::operator*(const Polynomial &other) const{
    Polynomial res;
    res.reserve(this->size() + other.size() - 1);
    for (int i = 0; i < other.size(); i++){
        res += (*this * other[i]) << i;
    }
    return res.trim();
}

Polynomial Polynomial::operator*(double scale) const{
    Polynomial res = *this;
    for (int i = 0; i < size(); i++){
        res[i] *= scale;
    }
    return res.trim();
}

Polynomial Polynomial::operator%(const Polynomial &other) const{
    int da = this->degree();
    int db = other.degree();
    Polynomial a = *this;

    if (db < 0) return {};

    while (da >= db && da >= 0) {
        double factor = a[da] / other[db];
        int shift = da - db;

        for (int i = 0; i <= db; ++i)
            a[i + shift] -= factor * other[i];

        a.trim();
        da = a.degree();
    }
    return a;
}

Polynomial Polynomial::operator<<(double degree) const{
    Polynomial res = *this;
    while(degree--){
        res.insert(res.begin(), 0);
    }
    return res;
}

Polynomial Polynomial::derivative() const{
    Polynomial res(size() - 1);
    for (int i = degree(); i > 0; i--){
        res[i - 1] = (*this)[i] * i;
    }
    return res;
}

Polynomial &Polynomial::trim(){
    while(this->size() > 0 && isZero(this->back())){
        this->pop_back();
    }
    return *this;
}

bool Polynomial::isConstant() const{
    return degree() == 0;
}

int Polynomial::degree() const{
    return size() - 1;
}

double Polynomial::evaluate(double x) const{
    double ans = 0;
    for (int i = degree(); i >= 0; i--){
        ans = ans * x + (*this)[i];
    }
    return ans;
}

std::string Polynomial::toString() const{
    std::ostringstream str;

    for (int i = degree(); i > 0; i--){
        if (isZero((*this)[i])) continue;
        if (i != degree()) str << " + ";
        str << format((*this)[i]).toStdString() << "x^" << i;
    }

    if (!isZero((*this)[0])) {
        if (degree() != 0) str << " + ";
        str << format((*this)[0]).toStdString();
    }
    return str.str();
}
