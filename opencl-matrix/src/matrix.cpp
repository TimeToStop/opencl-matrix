#include "matrix.h"

#include <math.h>
#include <numeric>

bool nearlyEquals(double a, double b)
{
    return std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * std::numeric_limits<double>::epsilon();
}
