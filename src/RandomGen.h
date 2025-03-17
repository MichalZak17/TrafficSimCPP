#pragma once

#include <random>

/**
 * @class RandomGen
 * @brief Handles random number generation for the traffic simulation.
 * 
 * The RandomGen class provides methods to generate random integers and doubles within specified ranges.
 * It uses the Mersenne Twister engine for random number generation.
 */
class RandomGen {
public:
    /**
     * @brief Constructor for the RandomGen class.
     * 
     * The constructor seeds the random number generator with a time-based seed.
     */
    RandomGen();
    
    /**
     * @brief Destructor for the RandomGen class.
     */
    ~RandomGen() = default;

    /**
     * @brief Generates a random integer within the specified range.
     * 
     * @param minVal The minimum value of the range (inclusive).
     * @param maxVal The maximum value of the range (inclusive).
     * @return A random integer within the specified range.
     */
    int randomInt(int minVal, int maxVal);

    /**
     * @brief Generates a random double within the specified range.
     * 
     * @param minVal The minimum value of the range (inclusive).
     * @param maxVal The maximum value of the range (inclusive).
     * @return A random double within the specified range.
     */
    double randomDouble(double minVal, double maxVal);

private:
    std::mt19937 m_engine; ///< Mersenne Twister random number engine.
};
