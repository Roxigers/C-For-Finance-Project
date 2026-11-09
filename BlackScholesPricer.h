#pragma once

#include "EuropeanVanillaOption.h"

class BlackScholesPricer {
private:
    EuropeanVanillaOption* _option;
    double _assetPrice;
    double _interestRate;
    double _volatility;

public:
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
                       double interest_rate, double volatility);

    double operator()() const;
    double delta() const;
};
