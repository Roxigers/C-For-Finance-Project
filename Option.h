#pragma once

#include <vector>

class Option {
private:
    double _expiry;

public:
    Option(double expiry);
    virtual ~Option() = default;

    double getExpiry() const;
    virtual double payoff(double z) const = 0;
    virtual double payoffPath(std::vector<double> path) const;
    virtual bool isAsianOption() const;
};
