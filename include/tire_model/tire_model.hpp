#pragma once

#include "tire_model/tire_types.hpp"
#include "tire_model/internal/tire_model_base.hpp"
#include <memory>
#include <string>

namespace tire_model {

/**
 * @brief Main tire model class
 * 
 * Automatically selects and instantiates the appropriate tire model from a .TIR file.
 */
class TireModel {
public:
    explicit TireModel(const std::string& filename);

    TireModel(const TireModel&) = delete;
    TireModel& operator=(const TireModel&) = delete;

    TireForces evaluate(const TireInput& input) const;
    
private:
    std::unique_ptr<internal::TireModelBase> model_;
};

} // namespace tire_model

