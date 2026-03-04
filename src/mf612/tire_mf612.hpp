#pragma once

#include "tire_model_base.hpp"
#include <map>
#include <string>

namespace tire_model {

/**
 * @brief MF6.1.2 tire model parameters structure
 */
struct MF612Params {
    // Units
    std::string LENGTH;
    std::string FORCE;

    // Dimension
    double UNLOADED_RADIUS = 0.0;

    // Operating Conditions
    double INFLPRES = 0.0;
    double NOMPRES = 0.0;

    // Vertical
    double FNOMIN = 0.0;
    double VERTICAL_STIFFNESS = 0.0;

    // Longitudinal force parameters
    double PCX1 = 0.0;
    double PDX1 = 0.0;
    double PDX2 = 0.0;
    double PDX3 = 0.0;
    double PEX1 = 0.0;
    double PEX2 = 0.0;
    double PEX3 = 0.0;
    double PEX4 = 0.0;
    double PKX1 = 0.0;
    double PKX2 = 0.0;
    double PKX3 = 0.0;
    double PHX1 = 0.0;
    double PHX2 = 0.0;
    double PVX1 = 0.0;
    double PVX2 = 0.0;
    double PPX1 = 0.0;
    double PPX2 = 0.0;
    double PPX3 = 0.0;
    double PPX4 = 0.0;

    // Longitudinal Combined Force Parameters
    double RBX1 = 0.0;
    double RBX2 = 0.0;
    double RBX3 = 0.0;
    double RCX1 = 0.0;
    double REX1 = 0.0;
    double REX2 = 0.0;
    double RHX1 = 0.0;

    // Lateral force parameters
    double PCY1 = 0.0;
    double PDY1 = 0.0;
    double PDY2 = 0.0;
    double PDY3 = 0.0;
    double PEY1 = 0.0;
    double PEY2 = 0.0;
    double PEY3 = 0.0;
    double PEY4 = 0.0;
    double PEY5 = 0.0;
    double PKY1 = 0.0;
    double PKY2 = 0.0;
    double PKY3 = 0.0;
    double PKY4 = 0.0;
    double PKY5 = 0.0;
    double PKY6 = 0.0;
    double PKY7 = 0.0;
    double PHY1 = 0.0;
    double PHY2 = 0.0;
    double PVY1 = 0.0;
    double PVY2 = 0.0;
    double PVY3 = 0.0;
    double PVY4 = 0.0;
    double PPY1 = 0.0;
    double PPY2 = 0.0;
    double PPY3 = 0.0;
    double PPY4 = 0.0;
    double PPY5 = 0.0;

    // Lateral Combined Parameters
    double RBY1 = 0.0;
    double RBY2 = 0.0;
    double RBY3 = 0.0;
    double RBY4 = 0.0;
    double RCY1 = 0.0;
    double REY1 = 0.0;
    double REY2 = 0.0;
    double RYH1 = 0.0;
    double RHY2 = 0.0;
    double RVY1 = 0.0;
    double RVY2 = 0.0;
    double RVY3 = 0.0;
    double RVY4 = 0.0;
    double RVY5 = 0.0;
    double RVY6 = 0.0;

    // Aligning moment parameters
    double QBZ1 = 0.0;
    double QBZ2 = 0.0;
    double QBZ3 = 0.0;
    double QBZ4 = 0.0;
    double QBZ5 = 0.0;
    double QBZ9 = 0.0;
    double QBZ10 = 0.0;
    double QCZ1 = 0.0;
    double QDZ1 = 0.0;
    double QDZ2 = 0.0;
    double QDZ3 = 0.0;
    double QDZ4 = 0.0;
    double QDZ6 = 0.0;
    double QDZ7 = 0.0;
    double QDZ8 = 0.0;
    double QDZ9 = 0.0;
    double QDZ10 = 0.0;
    double QDZ11 = 0.0;
    double QEZ1 = 0.0;
    double QEZ2 = 0.0;
    double QEZ3 = 0.0;
    double QEZ4 = 0.0;
    double QEZ5 = 0.0;
    double QHZ1 = 0.0;
    double QHZ2 = 0.0;
    double QHZ3 = 0.0;
    double QHZ4 = 0.0;
    double PPZ1 = 0.0;
    double PPZ2 = 0.0;

    // Aligning moment Combined Parameters
    double SSZ1 = 0.0;
    double SSZ2 = 0.0;
    double SSZ3 = 0.0;
    double SSZ4 = 0.0;
};

/**
 * @brief MF6.1.2 scaling factors structure
 */
struct MF612ScalingFactors {
    double LFZO = 1.0;
    double LMUX = 1.0;
    double LMUY = 1.0;
    double LXAL = 1.0;
    double LMUV = 0.0; // Should default to 0 unless trying to simulate slip speed with decaying friction
    double LKX = 1.0;
    double LKY = 1.0;
    double LCX = 1.0;
    double LCY = 1.0;
    double LEX = 1.0;
    double LEY = 1.0;
    double LHX = 1.0;
    double LHY = 1.0;
    double LVX = 1.0;
    double LVY = 1.0;
    double LKYC = 1.0;
    double LKZC = 1.0;
    double LTR = 1.0;
    double LRES = 1.0;
    double LYKA = 1.0;
    double LVYKA = 1.0;
    double LS = 1.0;
    double LMX = 1.0;
    double LVMX = 1.0;
    double LMY = 1.0;
};

/**
 * @brief MF6.1.2 tire model implementation (internal use only)
 * 
 * Implements the Magic Formula 6.1.2 tire model as specified in the TNO MF-Tyre/MF-Swift manual.
 */
class TireMF612 : public TireModelBase {
public:
    /**
     * @brief Construct a TireMF612 model from a parameter map
     *
     * @param params Map of parameter names to string values
     */
    explicit TireMF612(std::map<std::string, std::string> params);

    /**
     * @brief Construct a TireMF612 model from parameter structures
     *
     * @param params Tire parameters
     * @param scalingFactors Scaling factors
     */
    TireMF612(const MF612Params& params, const MF612ScalingFactors& scalingFactors);

    TireForces evaluate(const TireInput& input) const override;

private:
    MF612Params t;              // Tire parameters
    MF612ScalingFactors lambda; // Scaling factors
};

} // namespace tire_model

