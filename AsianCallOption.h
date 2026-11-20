#pragma once

#include "AsianOption.h"

class AsianCallOption : public AsianOption {
private:
    double _strike;

public:
    AsianCallOption(std::vector<double> timeSteps, double strike);

    double payoff(double z) const override;
};
AsianCallOption.cpp
cpp
#include "AsianCallOption.h"
#include <algorithm>

AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike)
    : AsianOption(timeSteps), _strike(strike) {
}

double AsianCallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}
