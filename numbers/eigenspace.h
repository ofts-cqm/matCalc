#ifndef EIGENSPACE_H
#define EIGENSPACE_H

#include "spanset.h"
#include <vector>

struct EigenSpace{
    std::vector<double> eigenValues;
    std::vector<SpanSet> eigenSpaces;
    int size;
};

#endif // EIGENSPACE_H
