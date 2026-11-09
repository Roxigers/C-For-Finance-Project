#include "BlackScholesPricer.h"
#include <cmath>
 
double normalCDF(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}
 
double normalPDF(double x) {
    return std::exp(-0.5 * x * x) / std::sqrt(2.0 * M_PI);
}
 
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
                                       double interest_rate, double volatility) {
    _option = option;
    _digitalOption = nullptr;
    _assetPrice = asset_price;
    _interestRate = interest_rate;
    _volatility = volatility;
}
 
BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price,
                                       double interest_rate, double volatility) {
    _option = nullptr;
    _digitalOption = option;
    _assetPrice = asset_price;
    _interestRate = interest_rate;
    _volatility = volatility;
}
 
double BlackScholesPricer::operator()() const {
    double S = _assetPrice;
    double r = _interestRate;
    double sigma = _volatility;
 
    if (_option != nullptr) {
        // Option vanille
        double K = _option->_strike;
        double T = _option->getExpiry();
        double d1 = (std::log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
 
        if (_option->GetOptionType() == optionType::call)
            return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
        else
            return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
    }
    else {
        // Option digitale
        double K = _digitalOption->_strike;
        double T = _digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
 
        if (_digitalOption->GetOptionType() == optionType::call)
            return std::exp(-r * T) * normalCDF(d2);
        else
            return std::exp(-r * T) * normalCDF(-d2);
    }
}
 
double BlackScholesPricer::delta() const {
    double S = _assetPrice;
    double r = _interestRate;
    double sigma = _volatility;
 
    if (_option != nullptr) {
        // Option vanille
        double K = _option->_strike;
        double T = _option->getExpiry();
        double d1 = (std::log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
 
        if (_option->GetOptionType() == optionType::call)
            return normalCDF(d1);
        else
            return normalCDF(d1) - 1;
    }
    else {
        // Option digitale
        double K = _digitalOption->_strike;
        double T = _digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        double d = std::exp(-r * T) * normalPDF(d2) / (S * sigma * std::sqrt(T));
 
        if (_digitalOption->GetOptionType() == optionType::call)
            return d;
        else
            return -d;
    }
}
