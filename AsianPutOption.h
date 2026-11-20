#pragma once

#include "AsianOption.h"

class AsianPutOption : public AsianOption {
private:
    double _strike;

public:
    AsianPutOption(std::vector<double> timeSteps, double strike);

    double payoff(double z) const override;
};
