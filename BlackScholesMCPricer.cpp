#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price,
                                           double interest_rate, double volatility) {
    _option = option;
    _initialPrice = initial_price;
    _interestRate = interest_rate;
    _volatility = volatility;
    _nbPaths = 0;
    _sum = 0;
    _sumSquares = 0;
}

int BlackScholesMCPricer::getNbPaths() const {
    return _nbPaths;
}

void BlackScholesMCPricer::generate(int nb_paths) {
    // Dates t1, ..., tm (m = 1 pour une option europeenne)
    std::vector<double> times;
    if (_option->isAsianOption())
        times = ((AsianOption*)_option)->getTimeSteps();
    else
        times.push_back(_option->getExpiry());

    int m = times.size();
    double T = _option->getExpiry();
    double sigma = _volatility;
    double r = _interestRate;
    std::vector<double> path(m);

    for (int p = 0; p < nb_paths; p++) {
        // Simulation d'un chemin S_t1, ..., S_tm
        double S = _initialPrice;
        double previousTime = 0;
        for (int k = 0; k < m; k++) {
            double dt = times[k] - previousTime;
            S = S * std::exp((r - sigma * sigma / 2) * dt + sigma * std::sqrt(dt) * MT::rand_norm());
            path[k] = S;
            previousTime = times[k];
        }

        double discountedPayoff = std::exp(-r * T) * _option->payoffPath(path);
        _sum += discountedPayoff;
        _sumSquares += discountedPayoff * discountedPayoff;
    }
    _nbPaths += nb_paths;
}

double BlackScholesMCPricer::operator()() const {
    if (_nbPaths == 0)
        throw std::logic_error("Aucun chemin genere : le prix n'est pas defini");
    return _sum / _nbPaths;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nbPaths == 0)
        throw std::logic_error("Aucun chemin genere : l'intervalle n'est pas defini");

    double mean = _sum / _nbPaths;
    double variance = _sumSquares / _nbPaths - mean * mean;
    double halfWidth = 1.96 * std::sqrt(variance / _nbPaths);

    std::vector<double> ci;
    ci.push_back(mean - halfWidth);
    ci.push_back(mean + halfWidth);
    return ci;
}