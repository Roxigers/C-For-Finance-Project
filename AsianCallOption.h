#pragma once

#include "AsianOption.h"

class AsianCallOption : public AsianOption {
private:
    double _strike;

public:
    AsianCallOption(std::vector<double> timeSteps, double strike);

    double payoff(double z) const override;
};
