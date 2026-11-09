#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price,
                     double up, double down, double interest_rate) {
    if (!(down < interest_rate && interest_rate < up))
        throw std::invalid_argument("Arbitrage : il faut D < R < U");

    _option = option;
    _depth = depth;
    _assetPrice = asset_price;
    _up = up;
    _down = down;
    _interestRate = interest_rate;
    _computed = false;

    _tree.setDepth(depth);
}

void CRRPricer::compute() {
    double q = (_interestRate - _down) / (_up - _down);

    for (int i = 0; i <= _depth; i++) {
        double S = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        _tree.setNode(_depth, i, _option->payoff(S));
    }

    for (int n = _depth - 1; n >= 0; n--) {
        for (int i = 0; i <= n; i++) {
            double H = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i))
                       / (1 + _interestRate);
            _tree.setNode(n, i, H);
        }
    }
    _computed = true;
}

double CRRPricer::get(int n, int i) {
    if (!_computed)
        compute();
    return _tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        double q = (_interestRate - _down) / (_up - _down);
        double sum = 0;
        for (int i = 0; i <= _depth; i++) {
            double logC = std::lgamma(_depth + 1) - std::lgamma(i + 1) - std::lgamma(_depth - i + 1);
            double proba = std::exp(logC + i * std::log(q) + (_depth - i) * std::log(1 - q));
            double S = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
            sum += proba * _option->payoff(S);
        }
        return sum / std::pow(1 + _interestRate, _depth);
    }

    if (!_computed)
        compute();
    return _tree.getNode(0, 0);
}
