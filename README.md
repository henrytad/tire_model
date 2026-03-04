# Tire Model Library

A C++ static library for tire force and moment calculations using various tire models. Currently implements the Magic Formula 6.1.2 (MF6.1.2) tire model, with support for additional models planned.

## Usage

### Basic Usage

```cpp
#include "tire_model/tire_model.hpp"
#include <iostream>

using namespace tire_model;

int main() {
    try {
        // Create a tire model from a .tir parameter file
        // The constructor automatically detects the model type from the file
        TireModel tire("path/to/tire_file.tir");
        
        // Prepare input parameters using TireInput struct
        TireInput input{
            .Fz = 5000.0,         // Vertical load (N)
            .alpha = 0.1,         // Slip angle (radians)
            .kappa = 0.05,        // Longitudinal slip ratio
            .gamma = 0.0,         // Camber angle (radians)
            .Vcx = 10.0           // Contact patch center velocity in x direction (m/s)
        };
        
        // Evaluate tire forces and moments
        TireForces forces = tire.evaluate(input);
        
        // Access results
        std::cout << "Fx (Longitudinal): " << forces.Fx << " N" << std::endl;
        std::cout << "Fy (Lateral): " << forces.Fy << " N" << std::endl;
        std::cout << "Mz (Aligning Moment): " << forces.Mz << " Nm" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

### Input Parameters

The `TireInput` structure contains all input parameters for tire force evaluation:

- `Fz` (double): Vertical load in Newtons (N)
- `alpha` (double): Slip angle in radians
- `kappa` (double): Longitudinal slip ratio
- `gamma` (double): Camber angle in radians
- `Vcx` (double): Contact patch center velocity in x direction (m/s)

### Output Structure

The `TireForces` structure contains the calculated tire forces and moments:

- `Fx` (double): Longitudinal force in Newtons (N)
- `Fy` (double): Lateral force in Newtons (N)
- `Mz` (double): Aligning moment in Newton-meters (Nm)

### API Reference

#### `TireModel` Class

The main class for client use. Automatically handles model selection internally.

**Constructor:**
- `explicit TireModel(const std::string& filename)`
  - Creates a tire model instance from a .tir parameter file
  - Automatically detects the model type from the file contents
  - Throws `std::runtime_error` if the file cannot be opened or parsed

**Methods:**
- `TireForces evaluate(const TireInput& input) const`
  - Evaluates tire forces and moments for the given input conditions
  - Returns a `TireForces` structure with `Fx`, `Fy`, and `Mz`
- `std::optional<TireParam> getParam(const std::string& key) const`
  - Looks up any raw parameter from the .tir file by key (e.g. `"VERTICAL_STIFFNESS"`, `"LENGTH"`, `"LCX"`)
  - Returns `std::nullopt` if the key is not present in the file
  - Numeric values are returned as `double`; text values (unit strings, labels) as `std::string`
  - `TireParam` is `std::variant<double, std::string>`

```cpp
// Numeric parameter
if (auto p = tire.getParam("VERTICAL_STIFFNESS")) {
    double stiffness = std::get<double>(*p); // 209651.0
}

// String parameter
if (auto p = tire.getParam("LENGTH")) {
    std::string unit = std::get<std::string>(*p); // "meter"
}
```

## Development

**Build** (from repo root):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

**Run example:** from `build/`, run `./tire_model_example` (or `tire_model_example.exe` on Windows).

**Run tests:** from repo root, `ctest --test-dir build -C Release` (or `cd build && ctest -C Release`).