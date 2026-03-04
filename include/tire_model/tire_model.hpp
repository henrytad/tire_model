#pragma once

#include "tire_model/tire_types.hpp"
#include <memory>
#include <optional>
#include <string>

namespace tire_model {

/**
 * @brief Main tire model class
 *
 * Automatically selects and instantiates the appropriate tire model from a .TIR file.
 * The concrete model implementation is selected based on the FITTYP field in the file.
 */
class TireModel {
public:
    explicit TireModel(const std::string& filename);
    ~TireModel();

    TireModel(const TireModel&);
    TireModel& operator=(const TireModel&);
    TireModel(TireModel&&) noexcept;
    TireModel& operator=(TireModel&&) noexcept;

    TireForces evaluate(const TireInput& input) const;

    /// Look up any raw parameter from the .tir file by key (e.g. "VERTICAL_STIFFNESS", "LENGTH").
    /// Returns nullopt if the key is not present.
    /// Numeric values are returned as double; text values as std::string.
    std::optional<TireParam> getParam(const std::string& key) const;

private:
    struct ModelVariant;
    std::unique_ptr<ModelVariant> impl_;
};

} // namespace tire_model

