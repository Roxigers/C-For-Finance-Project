#include "PutOption.h"
#include <algorithm>

PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

double PutOption::payoff(double z) const {
    return std::max(_strike - z, 0.0);
}

optionType PutOption::GetOptionType() const {
    return optionType::put;
}
