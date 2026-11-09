#pragma once

#include "Option.h"
#include "EuropeanVanillaOption.h"

class EuropeanDigitalOption : public Option {
private:
    double _strike;

    friend class BlackScholesPricer;
    friend class EuropeanDigitalCallOption;
    friend class EuropeanDigitalPutOption;

public:
    EuropeanDigitalOption(double expiry, double strike);

    virtual optionType GetOptionType() const = 0;
};
