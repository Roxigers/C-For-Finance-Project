#ifndef OPTION_H
#define OPTION_H

class Option {
private:
    double _expiry;

public:
    explicit Option(double expiry);
    virtual ~Option() = default;

    double getExpiry() const;

    virtual double payoff(double z) const = 0;
};

#endif
