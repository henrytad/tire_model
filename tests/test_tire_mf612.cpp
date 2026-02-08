#include <gtest/gtest.h>
#include "tire_model/internal/tire_mf612.hpp"
#include <cmath>

using namespace tire_model;
using namespace tire_model::internal;

TEST(TireMF612EvaluateTest, BasicEvaluation) {
    // Create tire model parameters from sample.tir
    MF612Params params{};
    params.LENGTH = "meter";
    params.FORCE = "Newton";
    params.UNLOADED_RADIUS = 0.3135;
    params.INFLPRES = 200000.0;
    params.NOMPRES = 200000.0;
    params.FNOMIN = 4000.0;
    params.VERTICAL_STIFFNESS = 209651.0;
    
    // Longitudinal force parameters
    params.PCX1 = 1.579;
    params.PDX1 = 1.0422;
    params.PDX2 = -0.08285;
    params.PDX3 = 0.0;
    params.PEX1 = 0.11113;
    params.PEX2 = 0.3143;
    params.PEX3 = -0.0;
    params.PEX4 = 0.001719;
    params.PKX1 = 21.687;
    params.PKX2 = 13.728;
    params.PKX3 = -0.4098;
    params.PHX1 = 2.1615e-04;
    params.PHX2 = 0.0011598;
    params.PVX1 = 2.20283e-5;
    params.PVX2 = 1.0568e-4;
    params.PPX1 = -0.3485;
    params.PPX2 = 0.37824;
    params.PPX3 = -0.09603;
    params.PPX4 = 0.06518;
    params.RBX1 = 13.046;
    params.RBX2 = 9.718;
    params.RBX3 = 0.0;
    params.RCX1 = 0.9995;
    params.REX1 = -0.4403;
    params.REX2 = -0.4663;
    params.RHX1 = -9.968e-5;
    
    // Lateral force parameters
    params.PCY1 = 1.337;
    params.PDY1 = 0.8785;
    params.PDY2 = -0.06452;
    params.PDY3 = 0.0;
    params.PEY1 = -0.8057;
    params.PEY2 = -0.6046;
    params.PEY3 = 0.09854;
    params.PEY4 = -6.697;
    params.PEY5 = 0.0;
    params.PKY1 = -15.324;
    params.PKY2 = 1.715;
    params.PKY3 = 0.3695;
    params.PKY4 = 2.0005;
    params.PKY5 = 0.0;
    params.PKY6 = -0.8987;
    params.PKY7 = -0.23303;
    params.PHY1 = -0.001806;
    params.PHY2 = 0.00352;
    params.PVY1 = -0.00661;
    params.PVY2 = 0.03592;
    params.PVY3 = -0.162;
    params.PVY4 = -0.4864;
    params.PPY1 = -0.6255;
    params.PPY2 = -0.06523;
    params.PPY3 = -0.16666;
    params.PPY4 = -0.2811;
    params.PPY5 = 0.0;
    params.RBY1 = 10.622;
    params.RBY2 = 7.82;
    params.RBY3 = 0.002037;
    params.RBY4 = 0.0;
    params.RCY1 = 1.0587;
    params.REY1 = 0.3148;
    params.REY2 = 0.004867;
    params.RYH1 = 0.009472;
    params.RHY2 = 0.009754;
    params.RVY1 = 0.05187;
    params.RVY2 = 4.853e-4;
    params.RVY3 = 0.0;
    params.RVY4 = 94.63;
    params.RVY5 = 1.8914;
    params.RVY6 = 23.8;
    
    // Aligning moment parameters
    params.QBZ1 = 12.035;
    params.QBZ2 = -1.33;
    params.QBZ3 = 0.0;
    params.QBZ4 = 0.176;
    params.QBZ5 = -0.14853;
    params.QBZ9 = 34.5;
    params.QBZ10 = 0.0;
    params.QCZ1 = 1.2923;
    params.QDZ1 = 0.09068;
    params.QDZ2 = -0.00565;
    params.QDZ3 = 0.3778;
    params.QDZ4 = 0.0;
    params.QDZ6 = 0.0017015;
    params.QDZ7 = -0.002091;
    params.QDZ8 = -0.1428;
    params.QDZ9 = 0.00915;
    params.QDZ10 = 0.0;
    params.QDZ11 = 0.0;
    params.QEZ1 = -1.7924;
    params.QEZ2 = 0.8975;
    params.QEZ3 = 0.0;
    params.QEZ4 = 0.2895;
    params.QEZ5 = -0.6786;
    params.QHZ1 = 0.0014333;
    params.QHZ2 = 0.0024087;
    params.QHZ3 = 0.24973;
    params.QHZ4 = -0.21205;
    params.PPZ1 = -0.4408;
    params.PPZ2 = 0.0;
    params.SSZ1 = 0.00918;
    params.SSZ2 = 0.03869;
    params.SSZ3 = 0.0;
    params.SSZ4 = 0.0;
    
    MF612ScalingFactors scalingFactors{};
    scalingFactors.LFZO = 1.0;
    scalingFactors.LCX = 1.0;
    scalingFactors.LMUX = 1.28;
    scalingFactors.LEX = 1.0;
    scalingFactors.LKX = 1.22;
    scalingFactors.LHX = 1.0;
    scalingFactors.LVX = 1.0;
    scalingFactors.LXAL = 1.0;
    scalingFactors.LCY = 1.0;
    scalingFactors.LMUY = 1.38;
    scalingFactors.LEY = 1.0;
    scalingFactors.LKY = 1.28;
    scalingFactors.LKYC = 1.18;
    scalingFactors.LKZC = 1.0;
    scalingFactors.LHY = 1.0;
    scalingFactors.LVY = 1.0;
    scalingFactors.LTR = 0.86;
    scalingFactors.LRES = 1.0;
    scalingFactors.LYKA = 1.08;
    scalingFactors.LVYKA = 1.0;
    scalingFactors.LS = 1.0;
    scalingFactors.LMX = 1.0;
    scalingFactors.LVMX = 1.0;
    scalingFactors.LMY = 1.0;

    TireMF612 tire(params, scalingFactors);
    
    TireInput input{};
    input.Fz = 4000.0;
    input.alpha = 0.05;
    input.kappa = 0.06;
    input.gamma = 0.07;
    input.Vcx = 1.0;
    
    TireForces forces = tire.evaluate(input);
    
    EXPECT_FLOAT_EQ(forces.Fx, 3902.7354);
    EXPECT_FLOAT_EQ(forces.Fy, -2511.1272);
    EXPECT_FLOAT_EQ(forces.Mz, -15.647495);
}

