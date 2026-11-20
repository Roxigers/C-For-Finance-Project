#include "AsianPutOption.h"
#include <algorithm>

AsianPutOption::AsianPutOption(std::vector<double> timeSteps, double strike)
    : AsianOption(timeSteps), _strike(strike) {
}

double AsianPutOption::payoff(double z) const {
    return std::max(_strike - z, 0.0);
}
