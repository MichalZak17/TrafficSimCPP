#include <iostream>
#include "TrafficSim.h"

// Entry point of the TrafficSimCPP application
int main() {
    // Create a TrafficSim instance
    TrafficSim simulator;

    // Initialize from config.txt (if found) and run
    if (!simulator.initialize("config/config.txt")) {
        std::cerr << "[Error] Failed to initialize simulator from config.\n";
        return 1;
    }

    simulator.runSimulation();

    std::cout << "[Info] Simulation complete. Check logs/simulation_log.txt for details.\n";
    return 0;
}
