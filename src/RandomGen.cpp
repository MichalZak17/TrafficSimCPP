#include "RandomGen.h"
#include <chrono>

RandomGen::RandomGen()
{
    // Seed with a time-based seed
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_engine.seed(static_cast<unsigned long>(seed));
}

int RandomGen::randomInt(int minVal, int maxVal) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    return dist(m_engine);
}

double RandomGen::randomDouble(double minVal, double maxVal) {
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    return dist(m_engine);
}
