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

`TireModel` uses the Pimpl idiom: it holds a `std::unique_ptr<ModelVariant>` where `ModelVariant` wraps a `std::variant<TireMF612>`. This keeps all implementation types out of the public header and ensures ABI stability.

### Private implementation (`src/`)

Root of `src/` holds shared infrastructure; one subdirectory per model implementation:

- `tire_model.cpp` — facade: parses the file, selects the model, owns the Pimpl
- `tire_model_base.hpp` — `TireModelBase` abstract base and `TireModelType` enum
- `tire_file_parser.hpp/cpp` — parses `.tir` files into `std::map<std::string, std::string>`; `detectModelType()` reads `FITTYP` (must be `61` for MF6.1.2)
- `mf612/tire_mf612.hpp/cpp` — MF6.1.2 implementation; `MF612Params` and `MF612ScalingFactors` structs; equation comments reference the TNO MF-Tyre manual (e.g. `// 4.E13`)

All private types are in the `tire_model` namespace. The `src/` include path is `PRIVATE` in CMake so clients cannot reach these headers.

### Adding a new tire model

1. Add a new `TireModelType` enum value in `src/tire_model_base.hpp`
2. Create `src/<name>/tire_<name>.hpp` and `src/<name>/tire_<name>.cpp`
3. Add the new type to `std::variant<...>` inside `TireModel::ModelVariant` in `src/tire_model.cpp`
4. Add a `case` in `makeModel()` in `src/tire_model.cpp`
5. Extend `detectModelType()` in `src/tire_file_parser.cpp` to recognise the new `FITTYP` value

### Consuming as a library (FetchContent)

Tests and examples are only built when this is the top-level CMake project. Downstream consumers via `FetchContent` or `add_subdirectory` get only the `tire_model` target. Options `TIRE_MODEL_BUILD_TESTS` and `TIRE_MODEL_BUILD_EXAMPLES` can override this.

### Key conventions

- All types (public and private) live in the `tire_model` namespace
- `TireInput.alpha` must be passed as `alpha_star` (`tan(alpha) * sgn(Vcx)`), not raw slip angle — see `src/mf612/tire_mf612.cpp:162`
- `LMUV` scaling factor defaults to `0.0` (not `1.0`) to avoid simulating velocity-dependent friction decay unless explicitly desired
