#include "PutOption.h"
#include <algorithm>

PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike)
{}


double PutOption::payoff(double z) const {
    return std::max(strike_ - z, 0.0);
}

optionType PutOption::GetOptionType() const {
    return put;
}