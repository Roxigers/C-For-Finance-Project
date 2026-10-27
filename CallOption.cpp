
#include "CallOption.h"
#include <algorithm>

CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

double CallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}

optionType CallOption::GetOptionType() const {
    return optionType::call;
}
