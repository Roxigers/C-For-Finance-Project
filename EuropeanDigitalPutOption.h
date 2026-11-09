#pragma once

#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);

    double payoff(double z) const override;
    optionType GetOptionType() const override;
};
