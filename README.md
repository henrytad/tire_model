# Tire Model Library

A C++ static library for tire force and moment calculations using various tire models. Currently implements the Magic Formula 6.1.2 (MF6.1.2) tire model, with support for additional models planned.

## Features

- **Unified Interface**: Single `TireModel` class for all tire models
- **Automatic Model Detection**: Automatically selects the appropriate tire model from parameter files
- **MF6.1.2 Support**: Full implementation of Magic Formula 6.1.2 tire model
- **Clean API**: Simple, consistent interface with structured input/output
- **Extensible**: Easy to add new tire model implementations
- **Internal Implementation**: All implementation details are hidden from clients

## Building

### Requirements

- CMake 3.15 or higher
- C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The static library will be created in `build/lib/` (or `build/` on some systems).

### Linking the Library

To use the library in your project, link against the `tire_model` static library:

```cmake
target_link_libraries(your_target tire_model)
```

Make sure to set the include directory:
```cmake
target_include_directories(your_target PRIVATE path/to/tire_model/include)
```

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
            .alpha_star = 0.1,    // Slip angle (tan(alpha) * sgn(Vcx))
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
- `alpha_star` (double): Slip angle, defined as `tan(alpha) * sgn(Vcx)`
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

**Note:** The `TireModel` class is non-copyable (copy constructor and assignment operator are deleted).

## File Structure

```
tire_model/
├── include/
│   └── tire_model/
│       ├── tire_model.hpp                    # Main header (include this)
│       └── internal/                         # Internal implementation (not for client use)
│           ├── tire_model_base.hpp           # Base interface class
│           ├── tire_file_parser.hpp          # File parsing utilities
│           └── mf612/
│               └── tire_mf612.hpp            # MF6.1.2 implementation
├── src/
│   ├── tire_model.cpp                        # TireModel implementation
│   ├── internal/
│   │   └── tire_file_parser.cpp             # File parsing implementation
│   └── mf612/
│       └── tire_mf612.cpp                   # MF6.1.2 implementation
├── examples/
│   ├── example_usage.cpp                     # Usage example
│   └── sample.tir                           # Sample tire parameter file
├── CMakeLists.txt
└── README.md
```

**Important:** Clients should only include `tire_model/tire_model.hpp`. All other headers in the `internal/` directory are implementation details and should not be included directly.

## Adding New Tire Models

To add a new tire model:

1. Create a new subdirectory under `include/tire_model/internal/` and `src/` (e.g., `mf61/`)
2. Create a header file in `include/tire_model/internal/<model_name>/tire_<model_name>.hpp`
3. Create an implementation file in `src/<model_name>/tire_<model_name>.cpp`
4. Create a new class inheriting from `tire_model::internal::TireModelBase`
5. Implement the virtual `evaluate` function: `TireForces evaluate(const TireInput& input) const override`
6. Add the model type to `TireModelType` enum in `include/tire_model/internal/tire_model_base.hpp`
7. Update the factory function in `src/tire_model.cpp` (in the anonymous namespace) to handle the new type
8. Add source files to `CMakeLists.txt`
9. Update model detection logic in `detectModelType()` in `src/internal/tire_file_parser.cpp` if needed

See `src/mf612/` for a complete implementation example.

## License

[Add your license here]

## Contributing

[Add contribution guidelines here]
