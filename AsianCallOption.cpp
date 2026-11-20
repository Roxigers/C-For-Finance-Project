#include "AsianCallOption.h"
#include <algorithm>

AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike)
    : AsianOption(timeSteps), _strike(strike) {
}

double AsianCallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}
