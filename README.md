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
