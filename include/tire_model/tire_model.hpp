#pragma once

#include "tire_model/tire_types.hpp"
#include "tire_model/internal/tire_mf612.hpp"
#include <string>
#include <variant>

namespace tire_model {

/**
 * @brief Main tire model class
 *
 * Automatically selects and instantiates the appropriate tire model from a .TIR file.
 */
class TireModel {
public:
    explicit TireModel(const std::string& filename);

    TireForces evaluate(const TireInput& input) const;

private:
    std::variant<internal::TireMF612> model_;
};

} // namespace tire_model

