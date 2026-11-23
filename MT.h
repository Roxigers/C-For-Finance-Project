#pragma once

#include <random>

class MT {
private:
    std::mt19937 _generator;

    MT();
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    static MT& getInstance();

public:
    static double rand_unif();
    static double rand_norm();
};