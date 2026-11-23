#pragma once

#include "Option.h"
#include <vector>

class BlackScholesMCPricer {
private:
    Option* _option;
    double _initialPrice;
    double _interestRate;
    double _volatility;
    int _nbPaths;
    double _sum;
    double _sumSquares;

public:
    BlackScholesMCPricer(Option* option, double initial_price,
                         double interest_rate, double volatility);

    int getNbPaths() const;
    void generate(int nb_paths);
    double operator()() const;
    std::vector<double> confidenceInterval() const;
};