#pragma once

#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"

class BlackScholesPricer {
private:
    EuropeanVanillaOption* _option;
    EuropeanDigitalOption* _digitalOption;
    double _assetPrice;
    double _interestRate;
    double _volatility;

public:
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
                       double interest_rate, double volatility);
    BlackScholesPricer(EuropeanDigitalOption* option, double asset_price,
                       double interest_rate, double volatility);

    double operator()() const;
    double delta() const;
};
