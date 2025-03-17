# TrafficSimCPP 🚦

A **terminal-based Traffic Intersection Simulator** written in **C++14**.  
This project demonstrates advanced C++ programming concepts including **multi-level inheritance, operator overloading, smart pointers, STL algorithms, move semantics, and file I/O**. The simulator models vehicles arriving and passing through intersections, applying traffic rules and random event generation—all without any GUI or online dependency.

## 🚀 Features

- **Multi-Level Inheritance**: A clear vehicle hierarchy (`Vehicle` → `LandVehicle` → `Car`, `Truck`, `Bus`) with polymorphism.
- **Operator Overloading**: Custom overloads (e.g., `operator<` and `operator==`) for comparing and printing objects.
- **Move Semantics**: Efficient object transfers using move constructors and move assignment operators.
- **Smart Pointers**: Management of dynamic memory using `std::unique_ptr` (available in C++14).
- **STL Algorithms & Containers**: Usage of `std::vector`, `std::map`, `std::sort`, `std::for_each`, and other algorithms to process simulation data.
- **Random Data Generation**: Utilize C++ random libraries for generating vehicle arrival times, speeds, and traffic light cycles.
- **File I/O**: Read simulation settings from configuration files and output logs/results to text files.
- **Simulation-Focused Design**: Emphasizes processing data rather than simply storing it, with no keyboard input during simulation.

## 📦 Installation

### Prerequisites
- A C++14 compliant compiler (GCC 5+, Clang 3.4+, MSVC 2015+)
- CMake 3.5+ (optional for build automation)

### Clone the Repository
```sh
git clone https://github.com/MichalZak17/TrafficSimCPP.git
cd TrafficSimCPP
```

### Build and Run
#### Using Make (Linux/macOS)
```sh
mkdir build && cd build
cmake ..
make
./traffic_sim
```

#### Using MSVC (Windows)
```sh
mkdir build
cd build
cmake ..
cmake --build .
traffic_sim.exe
```

## 📖 Usage

The simulation runs automatically using parameters from a **configuration file**. You can modify `config/config.txt` to adjust:
- Number of intersections
- Vehicle arrival frequency
- Traffic light timings

### Example Configuration (`config/config.txt`)
```ini
intersections = 3
vehicles_per_step = 5
max_simulation_steps = 100
traffic_light_green_time = 30
traffic_light_red_time = 20
```

## 🔧 Project Structure
```
TrafficSimCPP/
│── src/
│   ├── main.cpp         # Entry point
│   ├── TrafficObject.h  # Base class for all traffic entities
│   ├── Vehicle.h        # Abstract vehicle class with common attributes and virtual functions
│   ├── LandVehicle.h    # Derived class adding land-specific features
│   ├── Car.h            # Further derived class for Car
│   ├── Truck.h          # Further derived class for Truck
│   ├── Intersection.h   # Manages traffic flow and vehicle queues
│   ├── TrafficSim.h     # Simulation coordinator class
│   ├── RandomGen.h      # Handles random number generation
│── config/
│   ├── config.txt       # Simulation settings
│── logs/
│   ├── simulation_log.txt # Output logs
│── build/               # Compiled binaries (ignored in git)
│── CMakeLists.txt       # CMake build script
│── README.md            # This file
│── LICENSE              # Open-source license
```

## 🎯 Example Output

```
[Step 1] Vehicle ID=101 (Car) entered Intersection #2
[Step 2] Traffic light turned RED at Intersection #2
[Step 3] Vehicle ID=102 (Truck) waiting at Intersection #2
...
[Simulation Complete] 100 steps processed.
```

## 🛠️ Technologies Used

- **C++14**
- **STL Containers & Algorithms**
- **Smart Pointers (`std::unique_ptr`)**
- **Lambda Functions**
- **Move Semantics**
- **File I/O (fstream)**
- **Random Number Generation**

## 📜 License

Licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

## 🤝 Contributing

We welcome contributions! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m "Add feature"`).
4. Push to your fork and create a Pull Request.

## 💡 Future Improvements
- Enhance simulation realism by adding multi-lane intersections.
- Implement adaptive traffic light timings.
- Introduce varying vehicle behaviors and environmental factors.

## 🏆 Acknowledgments

Thanks to the contributors and maintainers who help make TrafficSimCPP a robust learning tool for modern C++ development.

## 🌟 Importance and Interesting Aspects of the Project

The TrafficSimCPP project is important and interesting for several reasons:

1. **Educational Value**:
   - Demonstrates advanced C++ programming concepts such as inheritance, polymorphism, smart pointers, and STL algorithms.

2. **Simulation Focus**:
   - Emphasizes data processing and simulation logic without relying on a graphical user interface.

3. **Real-World Application**:
   - Models real-world traffic scenarios, making it a valuable tool for understanding traffic flow and intersection management.

For more detailed instructions, please refer to the [DETAILED_GUIDE.md](DETAILED_GUIDE.md).

## 🖥️ Compiling the Project under Windows

To compile the TrafficSimCPP project under Windows, follow these detailed steps:

1. **Install Prerequisites**:
   - Install a C++14 compliant compiler (e.g., MSVC 2015+).
   - Install CMake 3.5+.

2. **Clone the Repository**:
   ```sh
   git clone https://github.com/MichalZak17/TrafficSimCPP.git
   cd TrafficSimCPP
   ```

3. **Create a Build Directory**:
   ```sh
   mkdir build
   cd build
   ```

4. **Generate Build Files with CMake**:
   ```sh
   cmake ..
   ```

5. **Build the Project**:
   ```sh
   cmake --build .
   ```

6. **Run the Executable**:
   ```sh
   traffic_sim.exe
   ```

### Troubleshooting Tips

- **Ensure CMake is in your PATH**:
  - Add the CMake binary directory to your system PATH.

- **Check Compiler Compatibility**:
  - Ensure your compiler supports C++14.

- **Verify Dependencies**:
  - Ensure all required libraries and headers are available.

- **Consult CMake Output**:
  - Review the CMake output for any errors or warnings.

## Detailed Documentation

### Class: `Car`

The `Car` class represents a car in the traffic simulation. It is derived from the `LandVehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
Car(int id, double speed);
```
- `id`: The unique identifier for the car.
- `speed`: The speed of the car.

#### Destructor
```cpp
~Car();
```

#### Method: `updateState`
```cpp
void updateState() override;
```
Updates the state of the car during each simulation step.

### Class: `Intersection`

The `Intersection` class represents a traffic intersection in the simulation. It manages the traffic light and the vehicles waiting at the intersection.

#### Constructor
```cpp
Intersection(int id);
```
- `id`: The unique identifier for the intersection.

#### Method: `setLightTimes`
```cpp
void setLightTimes(int green, int red);
```
Sets the traffic light times for the intersection.
- `green`: The duration of the green light.
- `red`: The duration of the red light.

#### Method: `addVehicle`
```cpp
void addVehicle(std::unique_ptr<Vehicle> v);
```
Adds a vehicle to the intersection's waiting queue.
- `v`: A unique pointer to the vehicle to be added.

#### Method: `update`
```cpp
void update();
```
Updates the state of the intersection, including the traffic light and the vehicles waiting at the intersection.

#### Method: `getId`
```cpp
int getId() const;
```
Returns the unique identifier of the intersection.

#### Method: `isGreen`
```cpp
bool isGreen() const;
```
Checks if the traffic light is green.

#### Method: `getWaitingCount`
```cpp
int getWaitingCount() const;
```
Returns the number of vehicles waiting at the intersection.

#### Method: `getThroughput`
```cpp
int getThroughput() const;
```
Returns the total number of vehicles that have passed through the intersection.

#### Method: `getPassedThisStep`
```cpp
int getPassedThisStep() const;
```
Returns the number of vehicles that passed through the intersection in the current step.

### Class: `LandVehicle`

The `LandVehicle` class represents a land vehicle in the traffic simulation. It is derived from the `Vehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
LandVehicle(int id, double speed, int wheels);
```
- `id`: The unique identifier for the land vehicle.
- `speed`: The speed of the land vehicle.
- `wheels`: The number of wheels of the land vehicle.

#### Destructor
```cpp
virtual ~LandVehicle();
```

#### Method: `getNumWheels`
```cpp
int getNumWheels() const;
```
Returns the number of wheels of the land vehicle.

### Class: `RandomGen`

The `RandomGen` class handles random number generation for the traffic simulation. It provides methods to generate random integers and doubles within specified ranges.

#### Constructor
```cpp
RandomGen();
```

#### Destructor
```cpp
~RandomGen();
```

#### Method: `randomInt`
```cpp
int randomInt(int minVal, int maxVal);
```
Generates a random integer within the specified range.
- `minVal`: The minimum value of the range (inclusive).
- `maxVal`: The maximum value of the range (inclusive).

#### Method: `randomDouble`
```cpp
double randomDouble(double minVal, double maxVal);
```
Generates a random double within the specified range.
- `minVal`: The minimum value of the range (inclusive).
- `maxVal`: The maximum value of the range (inclusive).

### Class: `TrafficObject`

The `TrafficObject` class is an abstract base class representing any traffic-related object. It defines a pure virtual method for updating the state of the object during each simulation step.

#### Destructor
```cpp
virtual ~TrafficObject();
```

#### Method: `updateState`
```cpp
virtual void updateState() = 0;
```
Pure virtual method for updating the state of the object. This method must be implemented by derived classes.

### Class: `TrafficSim`

The `TrafficSim` class manages the traffic simulation. It is responsible for initializing the simulation, loading the configuration, spawning vehicles, updating intersections, and logging the simulation progress.

#### Constructor
```cpp
TrafficSim();
```

#### Destructor
```cpp
~TrafficSim();
```

#### Method: `initialize`
```cpp
bool initialize(const std::string &configPath);
```
Initializes the simulation with the given configuration file.
- `configPath`: The path to the configuration file.

#### Method: `runSimulation`
```cpp
void runSimulation();
```
Runs the traffic simulation.

#### Method: `loadConfig`
```cpp
bool loadConfig(const std::string &path);
```
Loads the configuration from the specified file.
- `path`: The path to the configuration file.

#### Method: `logMessage`
```cpp
void logMessage(const std::string& message);
```
Logs a message to the simulation log file.
- `message`: The message to be logged.

#### Method: `spawnVehicles`
```cpp
void spawnVehicles();
```
Spawns vehicles at random intersections.

#### Method: `recordStepData`
```cpp
void recordStepData();
```
Records the state of the simulation at each step.

#### Method: `generateReport`
```cpp
void generateReport(const std::string &filename);
```
Generates a final report of the simulation.
- `filename`: The name of the report file.

### Class: `Truck`

The `Truck` class represents a truck in the traffic simulation. It is derived from the `LandVehicle` class and has specific attributes and behaviors.

#### Constructor
```cpp
Truck(int id, double speed);
```
- `id`: The unique identifier for the truck.
- `speed`: The speed of the truck.

#### Destructor
```cpp
~Truck();
```

#### Method: `updateState`
```cpp
void updateState() override;
```
Updates the state of the truck during each simulation step.

### Class: `Vehicle`

The `Vehicle` class is an abstract base class representing a vehicle in the traffic simulation. It defines common attributes and methods for vehicles, including ID, speed, and state update.

#### Constructor
```cpp
Vehicle(int id, double speed);
```
- `id`: The unique identifier for the vehicle.
- `speed`: The speed of the vehicle.

#### Destructor
```cpp
virtual ~Vehicle();
```

#### Copy Constructor
```cpp
Vehicle(const Vehicle& other);
```
- `other`: The Vehicle object to copy from.

#### Move Constructor
```cpp
Vehicle(Vehicle&& other) noexcept;
```
- `other`: The Vehicle object to move from.

#### Move Assignment Operator
```cpp
Vehicle& operator=(Vehicle&& other) noexcept;
```
- `other`: The Vehicle object to move from.

#### Method: `updateState`
```cpp
virtual void updateState() override = 0;
```
Pure virtual method for updating the state of the vehicle. This method must be implemented by derived classes.

#### Method: `getId`
```cpp
int getId() const;
```
Returns the unique identifier of the vehicle.

#### Method: `getSpeed`
```cpp
double getSpeed() const;
```
Returns the speed of the vehicle.
