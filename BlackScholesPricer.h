#pragma once

#include "EuropeanVanillaOption.h""

class BlackScholesPricer{
private:
    EuropeanVanillaOption* _option;
    double _assetPrice;
    double _interestRate;
    double _volatility;

public:
    BlackScholesPricer(EuropeanVanillaOption* option,
                    double assetPrice,
                    double interestRate,
                    double volatility);
    double operator()() const;
    double delta() const;
}
