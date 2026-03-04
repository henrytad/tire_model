#pragma once

#include "tire_model/tire_types.hpp"

namespace tire_model {

/**
 * @brief Enumeration of supported tire model types
 */
enum class TireModelType {
    MF612,  // Magic Formula 6.1.2
    // Future models can be added here
};

/**
 * @brief Base class for all tire model implementations
 */
class TireModelBase {
public:
    virtual ~TireModelBase() = default;

    virtual TireForces evaluate(const TireInput& input) const = 0;
};

} // namespace tire_model

