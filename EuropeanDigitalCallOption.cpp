#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

double EuropeanDigitalCallOption::payoff(double z) const {
    if (z >= _strike)
        return 1.0;
    return 0.0;
}

optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::call;
}
