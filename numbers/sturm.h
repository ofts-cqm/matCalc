#ifndef STURM_H
#define STURM_H

#include "polynomial.h"
#include <set>

struct Range{
    double upper;
    double lower;
};

class Sturm : public std::vector<Polynomial>
{
public:
    explicit Sturm(const Polynomial &src);

    int countSignChange(double x) const;

    int countRoots(const Range &range) const;

    void isolate(const Range &range, std::vector<Range> &intervals) const;

    std::set<double> roots() const;

private:
    Polynomial p;
};

#endif // STURM_H
