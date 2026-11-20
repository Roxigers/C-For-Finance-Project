#include "AsianOption.h"

AsianOption::AsianOption(std::vector<double> timeSteps)
    : Option(timeSteps.back()), _timeSteps(timeSteps) {
}

std::vector<double> AsianOption::getTimeSteps() const {
    return _timeSteps;
}

double AsianOption::payoffPath(std::vector<double> path) const {
    double sum = 0;
    for (int k = 0; k < (int)path.size(); k++)
        sum += path[k];
    return payoff(sum / path.size());
}

bool AsianOption::isAsianOption() const {
    return true;
}
