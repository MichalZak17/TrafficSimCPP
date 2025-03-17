#include <iostream>
#include "TrafficSim.h"

/**
 * @brief Entry point of the TrafficSimCPP application.
 * 
 * This function initializes the TrafficSim instance, loads the configuration, and runs the simulation.
 * 
 * @return int Returns 0 on successful completion, 1 on error.
 */
int main() {
    // Create a TrafficSim instance
    TrafficSim simulator;

    // Initialize from config.txt (if found) and run
    if (!simulator.initialize("config/config.txt")) {
        std::cerr << "[Error] Failed to initialize simulator from config.\n";
        return 1;
    }

    // Run the simulation
    simulator.runSimulation();

    std::cout << "[Info] Simulation complete. Check logs/simulation_log.txt for details.\n";
    return 0;
}
