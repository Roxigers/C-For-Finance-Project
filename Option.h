#pragma once

class Option {
private:
    double _expiry;

public:
    Option(double expiry);
    virtual ~Option() = default;

    double getExpiry() const;
    virtual double payoff(double z) const = 0;
};
