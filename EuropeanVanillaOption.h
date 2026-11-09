#pragma once

#include "Option.h"

enum class optionType {
    call,
    put
};

class EuropeanVanillaOption : public Option {
private:
    double _strike;

    friend class BlackScholesPricer;
    friend class CallOption;
    friend class PutOption;

public:
    EuropeanVanillaOption(double expiry, double strike);

    virtual optionType GetOptionType() const = 0;
};
