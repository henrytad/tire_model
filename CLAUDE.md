# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

```bash
# Configure (from repo root)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release
```

## Tests

```bash
# Run all tests (from repo root)
ctest --test-dir build -C Release

# Run a specific test binary directly
./build/tire_model_tests

# Run a specific test by name
./build/tire_model_tests --gtest_filter=TireMF612EvaluateTest.BasicEvaluation
```

## Run Example

```bash
./build/tire_model_example
```

## Architecture

This is a C++20 static library (`tire_model`) for computing tire forces and moments using the Magic Formula 6.1.2 (MF6.1.2) model.

### Public API (`include/tire_model/`)

- `tire_types.hpp` — `TireInput` and `TireForces` structs (inputs/outputs for evaluation)
- `tire_model.hpp` — `TireModel` class: the only public-facing class clients use

`TireModel` holds a `std::variant<TireMF612>` internally. New model types are added to this variant and a new `case` in the `makeModel()` factory in `src/tire_model.cpp`.

### Internal implementation (`include/tire_model/internal/`, `src/`)

- `tire_model_base.hpp` — `TireModelBase` abstract base class and `TireModelType` enum
- `tire_mf612.hpp` / `src/mf612/tire_mf612.cpp` — MF6.1.2 implementation with `MF612Params` and `MF612ScalingFactors` structs; equation comments reference the TNO MF-Tyre manual (e.g. `// 4.E13`)
- `tire_file_parser.hpp` / `src/internal/tire_file_parser.cpp` — parses `.tir` files into a `std::map<std::string, std::string>`, then `detectModelType()` checks `FITTYP` (must equal `61` for MF6.1.2)

### Adding a new tire model

1. Add a new `TireModelType` enum value in `tire_model_base.hpp`
2. Create `include/tire_model/internal/tire_<name>.hpp` and `src/<name>/tire_<name>.cpp`
3. Add the new type to the `std::variant<...>` in `tire_model.hpp`
4. Add a `case` in `makeModel()` in `src/tire_model.cpp`
5. Extend `detectModelType()` in `tire_file_parser.cpp` to recognize the new `FITTYP` value

### Consuming as a library (FetchContent)

Tests and examples are only built when this is the top-level CMake project. Downstream consumers via `FetchContent` or `add_subdirectory` get only the static library target `tire_model`. Options `TIRE_MODEL_BUILD_TESTS` and `TIRE_MODEL_BUILD_EXAMPLES` can override this behaviour.

### Key conventions

- All public types live in the `tire_model` namespace; internal types live in `tire_model::internal`
- `TireInput.alpha` must be passed as `alpha_star` (`tan(alpha) * sgn(Vcx)`), not raw slip angle in radians — see comment in `tire_mf612.cpp:162`
- `LMUV` scaling factor defaults to `0.0` (not `1.0`) to avoid simulating velocity-dependent friction decay unless explicitly desired
