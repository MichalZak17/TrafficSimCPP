#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <memory>
#include "Intersection.h"
#include "RandomGen.h"

#pragma once
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Intersection.h"
#include "RandomGen.h"

class TrafficSim {
public:
    TrafficSim();
    ~TrafficSim();

    bool initialize(const std::string &configPath);
    void runSimulation();

private:
    bool loadConfig(const std::string &path);
    void logMessage(const std::string& message);

    // Existing
    void spawnVehicles();

    // -----------------------------------------------------------
    // 1) ADD THESE STRUCTS AND NEW METHODS
    // -----------------------------------------------------------

    // Info about a single intersection at a particular simulation step
    struct IntersectionRecord
    {
        int id;
        bool isGreen;
        int waitingCount;
        int passedThisStep;
        int totalThroughput;
    };

    // Info about vehicles that spawned at a particular step
    struct SpawnRecord
    {
        int stepNumber;
        int vehicleId;
        std::string vehicleType; // e.g. "Car" or "Truck"
        int intersectionAssigned;
    };

    // One "snapshot" of the simulation after a single step
    struct StepRecord
    {
        int stepNumber;
        std::vector<IntersectionRecord> intersectionStates;
        std::vector<SpawnRecord> spawnedVehicles;
    };

    // Keep a record for each step of the simulation
    std::vector<StepRecord> m_simHistory;

    // Called internally each step to record data
    void recordStepData();

    // Called at end of simulation to generate final report
    void generateReport(const std::string &filename);

    std::map<int, Intersection> m_intersections;
    int m_numIntersections;
    int m_vehiclesPerStep;
    int m_maxSteps;
    RandomGen m_rng;  // random generator

    // Traffic light times (shared by all intersections for simplicity)
    int m_greenTime;
    int m_redTime;

    // For logging
    std::ofstream m_logFile;
    int m_currentStep;
};
