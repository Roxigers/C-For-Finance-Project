#include "Option.h"

Option::Option(double expiry) : _expiry(expiry) {
}

double Option::getExpiry() const {
    return _expiry;
}

double Option::payoffPath(std::vector<double> path) const {
    return payoff(path.back());
}

bool Option::isAsianOption() const {
    return false;
}
