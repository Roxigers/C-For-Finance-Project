#pragma once

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {
private:
    Option* _option;
    int _depth;
    double _assetPrice;
    double _up;
    double _down;
    double _interestRate;
    BinaryTree<double> _tree;
    bool _computed;

public:
    CRRPricer(Option* option, int depth, double asset_price,
              double up, double down, double interest_rate);

    void compute();
    double get(int n, int i);
    double operator()(bool closed_form = false);
};
