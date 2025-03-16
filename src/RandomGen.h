#pragma once

#include <random>

class RandomGen {
public:
    RandomGen();
    ~RandomGen() = default;

    // Return an integer in [minVal, maxVal]
    int randomInt(int minVal, int maxVal);

    // Return a double in [minVal, maxVal]
    double randomDouble(double minVal, double maxVal);

private:
    std::mt19937 m_engine;
};
