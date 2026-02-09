#include "sturm.h"
#include "polynomial.h"
#include "../util.h"

Sturm::Sturm(const Polynomial &src): std::vector<Polynomial>(), p(src) {
    push_back(src);
    push_back(src.derivative());

    while(true){
        Polynomial remainder = (* this)[size() - 2] % this->back();
        push_back(-remainder);
        if (remainder.isConstant()) break;
    }
}

int sign(double x) {
    if (isZero(x)) return 0;
    return x > 0 ? 1 : -1;
}

int Sturm::countSignChange(double x) const {
    int prevSign = 0;
    int changes = 0;

    for (const Polynomial &p : *this) {
        double val = p.evaluate(x);
        int s = sign(val);

        if (s == 0) continue;
        if (prevSign != 0 && s != prevSign)
            changes++;

        prevSign = s;
    }
    return changes;
}

int Sturm::countRoots(const Range &range) const{
    return countSignChange(range.lower) - countSignChange(range.upper);
}

void Sturm::isolate(const Range &range, std::vector<Range> &intervals) const{
    int cnt = countRoots(range);
    if (cnt == 0) return;

    if (cnt == 1){
        intervals.push_back(range);
        return;
    }

    double mid = (range.upper + range.lower) / 2.0;
    isolate({range.upper, mid}, intervals);
    isolate({mid, range.lower}, intervals);
}

double bisection(const Polynomial &p, const Range &r) {
    double fa = p.evaluate(r.upper);
    double fb = p.evaluate(r.lower);

    int a = r.upper;
    int b = r.lower;

    for (int i = 0; i < 100; ++i) {
        double m = (a + b) / 2.0;
        double fm = p.evaluate(m);

        if (isZero(fm))
            return m;

        if (fa * fm < 0) {
            b = m;
            fb = fm;
        } else {
            a = m;
            fa = fm;
        }
    }
    return (a + b) / 2.0;
}

double newton(const Polynomial &p, double x0) {
    Polynomial dp = p.derivative();

    for (int i = 0; i < 10; ++i) {
        double fx = p.evaluate(x0);
        double dfx = dp.evaluate(x0);
        if (isZero(dfx))
            break;
        x0 -= fx / dfx;
    }
    return x0;
}

std::vector<double> Sturm::roots() const {
    // Cauchy bound
    double an = p[p.degree()];
    double R = 1;
    for (int i = 0; i < p.degree(); ++i)
        R = std::max(R, fabs(p[i] / an));
    R = 1 + R;

    vector<Range> intervals;
    isolate({R, -R}, intervals);

    std::vector<double> roots;

    for (const Range &r: intervals) {
        double root = bisection(p, r);
        root = newton(p, root); // polish
        roots.push_back(root);
    }

    sort(roots.begin(), roots.end());
    return roots;
}
