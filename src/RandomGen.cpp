#include "RandomGen.h"
#include <chrono>

/**
 * @class RandomGen
 * @brief Handles random number generation for the traffic simulation.
 * 
 * The RandomGen class provides methods to generate random integers and doubles within specified ranges.
 * It uses the Mersenne Twister engine for random number generation.
 */

/**
 * @brief Constructor for the RandomGen class.
 * 
 * The constructor seeds the random number generator with a time-based seed.
 */
RandomGen::RandomGen()
{
    // Seed with a time-based seed
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_engine.seed(static_cast<unsigned long>(seed));
}

/**
 * @brief Generates a random integer within the specified range.
 * 
 * @param minVal The minimum value of the range (inclusive).
 * @param maxVal The maximum value of the range (inclusive).
 * @return A random integer within the specified range.
 */
int RandomGen::randomInt(int minVal, int maxVal) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    return dist(m_engine);
}

/**
 * @brief Generates a random double within the specified range.
 * 
 * @param minVal The minimum value of the range (inclusive).
 * @param maxVal The maximum value of the range (inclusive).
 * @return A random double within the specified range.
 */
double RandomGen::randomDouble(double minVal, double maxVal) {
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    return dist(m_engine);
}
