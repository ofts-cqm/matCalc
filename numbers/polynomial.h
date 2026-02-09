#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>

class Polynomial: private std::vector<double>
{
public:
    Polynomial();
    Polynomial(const Polynomial &);
    Polynomial(Polynomial &&);
    Polynomial(std::initializer_list<double> list);

    using ::Polynomial::vector::operator=;
    using ::Polynomial::vector::operator[];

    Polynomial operator+(const Polynomial &other) const;
    Polynomial &operator+=(const Polynomial &other);
    Polynomial operator-(const Polynomial &other) const;
    Polynomial operator-() const;
    Polynomial operator*(const Polynomial &other) const;
    Polynomial operator*(double scale) const;
    Polynomial operator%(const Polynomial &other) const;
    Polynomial operator<<(double degree) const;
    Polynomial derivative() const;

    bool isConstant() const;
    int degree() const;
    std::string toString() const;
    double evaluate(double x) const;

private:
    Polynomial(int length, const Polynomial &src = {});

    Polynomial &trim();
};

#endif // POLYNOMIAL_H
