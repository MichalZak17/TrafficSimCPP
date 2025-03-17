#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <memory>
#include "Intersection.h"
#include "RandomGen.h"

/**
 * @class TrafficSim
 * @brief Manages the traffic simulation.
 * 
 * The TrafficSim class is responsible for initializing the simulation, loading the configuration, spawning vehicles, updating intersections, and logging the simulation progress.
 */
class TrafficSim {
public:
    /**
     * @brief Constructor for the TrafficSim class.
     */
    TrafficSim();

    /**
     * @brief Destructor for the TrafficSim class.
     */
    ~TrafficSim();

    /**
     * @brief Initializes the simulation with the given configuration file.
     * 
     * @param configPath The path to the configuration file.
     * @return True if initialization is successful, false otherwise.
     */
    bool initialize(const std::string &configPath);

    /**
     * @brief Runs the traffic simulation.
     */
    void runSimulation();

private:
    /**
     * @brief Loads the configuration from the specified file.
     * 
     * @param path The path to the configuration file.
     * @return True if the configuration is loaded successfully, false otherwise.
     */
    bool loadConfig(const std::string &path);

    /**
     * @brief Logs a message to the simulation log file.
     * 
     * @param message The message to be logged.
     */
    void logMessage(const std::string& message);

    /**
     * @brief Spawns vehicles at random intersections.
     */
    void spawnVehicles();

    /**
     * @brief Records the state of the simulation at each step.
     */
    void recordStepData();

    /**
     * @brief Generates a final report of the simulation.
     * 
     * @param filename The name of the report file.
     */
    void generateReport(const std::string &filename);

    /**
     * @struct IntersectionRecord
     * @brief Stores information about a single intersection at a particular simulation step.
     */
    struct IntersectionRecord {
        int id; ///< The unique identifier of the intersection.
        bool isGreen; ///< Indicates if the traffic light is green.
        int waitingCount; ///< The number of vehicles waiting at the intersection.
        int passedThisStep; ///< The number of vehicles that passed through the intersection in the current step.
        int totalThroughput; ///< The total number of vehicles that have passed through the intersection.
    };

    /**
     * @struct SpawnRecord
     * @brief Stores information about vehicles that spawned at a particular step.
     */
    struct SpawnRecord {
        int stepNumber; ///< The simulation step number.
        int vehicleId; ///< The unique identifier of the vehicle.
        std::string vehicleType; ///< The type of the vehicle (e.g., "Car" or "Truck").
        int intersectionAssigned; ///< The intersection where the vehicle was assigned.
    };

    /**
     * @struct StepRecord
     * @brief Stores a snapshot of the simulation after a single step.
     */
    struct StepRecord {
        int stepNumber; ///< The simulation step number.
        std::vector<IntersectionRecord> intersectionStates; ///< The states of the intersections at the current step.
        std::vector<SpawnRecord> spawnedVehicles; ///< The vehicles spawned at the current step.
    };

    std::map<int, Intersection> m_intersections; ///< The map of intersections in the simulation.
    int m_numIntersections; ///< The number of intersections in the simulation.
    int m_vehiclesPerStep; ///< The number of vehicles to spawn per simulation step.
    int m_maxSteps; ///< The maximum number of simulation steps.
    RandomGen m_rng; ///< The random number generator for the simulation.

    int m_greenTime; ///< The duration of the green light for all intersections.
    int m_redTime; ///< The duration of the red light for all intersections.

    std::ofstream m_logFile; ///< The log file for the simulation.
    int m_currentStep; ///< The current simulation step.

    std::vector<StepRecord> m_simHistory; ///< The history of the simulation steps.
};
