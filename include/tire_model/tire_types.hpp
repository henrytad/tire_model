#pragma once

#include <string>
#include <variant>

namespace tire_model {

// Value type returned by TireModel::getParam().
// Holds either a numeric value (double) or a text value (std::string).
using TireParam = std::variant<double, std::string>;

/**
 * @brief Input structure for tire model evaluation
 */
struct TireInput {
    double Fz;          // Vertical load (N)
    double alpha;       // Slip angle (radians)
    double kappa;       // Longitudinal slip ratio
    double gamma;       // Camber angle (radians)
    double Vcx;         // Contact patch center velocity in x direction (m/s)
};

/**
 * @brief Result structure containing tire forces and moments
 */
struct TireForces {
    double Fx;  // Longitudinal force
    double Fy;  // Lateral force
    double Mz;  // Aligning moment
};

} // namespace tire_model

