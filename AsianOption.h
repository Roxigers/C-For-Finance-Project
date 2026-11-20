#pragma once

#include "Option.h"
#include <vector>

class AsianOption : public Option {
private:
    std::vector<double> _timeSteps;

public:
    AsianOption(std::vector<double> timeSteps);

    std::vector<double> getTimeSteps() const;
    double payoffPath(std::vector<double> path) const override;
    bool isAsianOption() const override;
};
