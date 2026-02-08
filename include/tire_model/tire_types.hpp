#pragma once

namespace tire_model {

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

