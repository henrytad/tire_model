#include "mf612/tire_mf612.hpp"
#include "tire_file_parser.hpp"

#include <cmath>
#include <numbers>
#include <utility>

using namespace tire_model;

TireMF612::TireMF612(std::map<std::string, std::string> params)
    : TireModelBase(std::move(params))
    , t(MF612Params{
            .LENGTH = getStringFromMap(rawParams(), "LENGTH"),
            .FORCE = getStringFromMap(rawParams(), "FORCE"),
            .UNLOADED_RADIUS = getDoubleFromMap(rawParams(), "UNLOADED_RADIUS"),
            .INFLPRES = getDoubleFromMap(rawParams(), "INFLPRES"),
            .NOMPRES = getDoubleFromMap(rawParams(), "NOMPRES"),
            .FNOMIN = getDoubleFromMap(rawParams(), "FNOMIN"),
            .VERTICAL_STIFFNESS = getDoubleFromMap(rawParams(), "VERTICAL_STIFFNESS"),
            .PCX1 = getDoubleFromMap(rawParams(), "PCX1"),
            .PDX1 = getDoubleFromMap(rawParams(), "PDX1"),
            .PDX2 = getDoubleFromMap(rawParams(), "PDX2"),
            .PDX3 = getDoubleFromMap(rawParams(), "PDX3"),
            .PEX1 = getDoubleFromMap(rawParams(), "PEX1"),
            .PEX2 = getDoubleFromMap(rawParams(), "PEX2"),
            .PEX3 = getDoubleFromMap(rawParams(), "PEX3"),
            .PEX4 = getDoubleFromMap(rawParams(), "PEX4"),
            .PKX1 = getDoubleFromMap(rawParams(), "PKX1"),
            .PKX2 = getDoubleFromMap(rawParams(), "PKX2"),
            .PKX3 = getDoubleFromMap(rawParams(), "PKX3"),
            .PHX1 = getDoubleFromMap(rawParams(), "PHX1"),
            .PHX2 = getDoubleFromMap(rawParams(), "PHX2"),
            .PVX1 = getDoubleFromMap(rawParams(), "PVX1"),
            .PVX2 = getDoubleFromMap(rawParams(), "PVX2"),
            .PPX1 = getDoubleFromMap(rawParams(), "PPX1"),
            .PPX2 = getDoubleFromMap(rawParams(), "PPX2"),
            .PPX3 = getDoubleFromMap(rawParams(), "PPX3"),
            .PPX4 = getDoubleFromMap(rawParams(), "PPX4"),
            .RBX1 = getDoubleFromMap(rawParams(), "RBX1"),
            .RBX2 = getDoubleFromMap(rawParams(), "RBX2"),
            .RBX3 = getDoubleFromMap(rawParams(), "RBX3"),
            .RCX1 = getDoubleFromMap(rawParams(), "RCX1"),
            .REX1 = getDoubleFromMap(rawParams(), "REX1"),
            .REX2 = getDoubleFromMap(rawParams(), "REX2"),
            .RHX1 = getDoubleFromMap(rawParams(), "RHX1"),
            .PCY1 = getDoubleFromMap(rawParams(), "PCY1"),
            .PDY1 = getDoubleFromMap(rawParams(), "PDY1"),
            .PDY2 = getDoubleFromMap(rawParams(), "PDY2"),
            .PDY3 = getDoubleFromMap(rawParams(), "PDY3"),
            .PEY1 = getDoubleFromMap(rawParams(), "PEY1"),
            .PEY2 = getDoubleFromMap(rawParams(), "PEY2"),
            .PEY3 = getDoubleFromMap(rawParams(), "PEY3"),
            .PEY4 = getDoubleFromMap(rawParams(), "PEY4"),
            .PEY5 = getDoubleFromMap(rawParams(), "PEY5"),
            .PKY1 = getDoubleFromMap(rawParams(), "PKY1"),
            .PKY2 = getDoubleFromMap(rawParams(), "PKY2"),
            .PKY3 = getDoubleFromMap(rawParams(), "PKY3"),
            .PKY4 = getDoubleFromMap(rawParams(), "PKY4"),
            .PKY5 = getDoubleFromMap(rawParams(), "PKY5"),
            .PKY6 = getDoubleFromMap(rawParams(), "PKY6"),
            .PKY7 = getDoubleFromMap(rawParams(), "PKY7"),
            .PHY1 = getDoubleFromMap(rawParams(), "PHY1"),
            .PHY2 = getDoubleFromMap(rawParams(), "PHY2"),
            .PVY1 = getDoubleFromMap(rawParams(), "PVY1"),
            .PVY2 = getDoubleFromMap(rawParams(), "PVY2"),
            .PVY3 = getDoubleFromMap(rawParams(), "PVY3"),
            .PVY4 = getDoubleFromMap(rawParams(), "PVY4"),
            .PPY1 = getDoubleFromMap(rawParams(), "PPY1"),
            .PPY2 = getDoubleFromMap(rawParams(), "PPY2"),
            .PPY3 = getDoubleFromMap(rawParams(), "PPY3"),
            .PPY4 = getDoubleFromMap(rawParams(), "PPY4"),
            .PPY5 = getDoubleFromMap(rawParams(), "PPY5"),
            .RBY1 = getDoubleFromMap(rawParams(), "RBY1"),
            .RBY2 = getDoubleFromMap(rawParams(), "RBY2"),
            .RBY3 = getDoubleFromMap(rawParams(), "RBY3"),
            .RBY4 = getDoubleFromMap(rawParams(), "RBY4"),
            .RCY1 = getDoubleFromMap(rawParams(), "RCY1"),
            .REY1 = getDoubleFromMap(rawParams(), "REY1"),
            .REY2 = getDoubleFromMap(rawParams(), "REY2"),
            .RYH1 = getDoubleFromMap(rawParams(), "RYH1"),
            .RHY2 = getDoubleFromMap(rawParams(), "RHY2"),
            .RVY1 = getDoubleFromMap(rawParams(), "RVY1"),
            .RVY2 = getDoubleFromMap(rawParams(), "RVY2"),
            .RVY3 = getDoubleFromMap(rawParams(), "RVY3"),
            .RVY4 = getDoubleFromMap(rawParams(), "RVY4"),
            .RVY5 = getDoubleFromMap(rawParams(), "RVY5"),
            .RVY6 = getDoubleFromMap(rawParams(), "RVY6"),
            .QBZ1 = getDoubleFromMap(rawParams(), "QBZ1"),
            .QBZ2 = getDoubleFromMap(rawParams(), "QBZ2"),
            .QBZ3 = getDoubleFromMap(rawParams(), "QBZ3"),
            .QBZ4 = getDoubleFromMap(rawParams(), "QBZ4"),
            .QBZ5 = getDoubleFromMap(rawParams(), "QBZ5"),
            .QBZ9 = getDoubleFromMap(rawParams(), "QBZ9"),
            .QBZ10 = getDoubleFromMap(rawParams(), "QBZ10"),
            .QCZ1 = getDoubleFromMap(rawParams(), "QCZ1"),
            .QDZ1 = getDoubleFromMap(rawParams(), "QDZ1"),
            .QDZ2 = getDoubleFromMap(rawParams(), "QDZ2"),
            .QDZ3 = getDoubleFromMap(rawParams(), "QDZ3"),
            .QDZ4 = getDoubleFromMap(rawParams(), "QDZ4"),
            .QDZ6 = getDoubleFromMap(rawParams(), "QDZ6"),
            .QDZ7 = getDoubleFromMap(rawParams(), "QDZ7"),
            .QDZ8 = getDoubleFromMap(rawParams(), "QDZ8"),
            .QDZ9 = getDoubleFromMap(rawParams(), "QDZ9"),
            .QDZ10 = getDoubleFromMap(rawParams(), "QDZ10"),
            .QDZ11 = getDoubleFromMap(rawParams(), "QDZ11"),
            .QEZ1 = getDoubleFromMap(rawParams(), "QEZ1"),
            .QEZ2 = getDoubleFromMap(rawParams(), "QEZ2"),
            .QEZ3 = getDoubleFromMap(rawParams(), "QEZ3"),
            .QEZ4 = getDoubleFromMap(rawParams(), "QEZ4"),
            .QEZ5 = getDoubleFromMap(rawParams(), "QEZ5"),
            .QHZ1 = getDoubleFromMap(rawParams(), "QHZ1"),
            .QHZ2 = getDoubleFromMap(rawParams(), "QHZ2"),
            .QHZ3 = getDoubleFromMap(rawParams(), "QHZ3"),
            .QHZ4 = getDoubleFromMap(rawParams(), "QHZ4"),
            .PPZ1 = getDoubleFromMap(rawParams(), "PPZ1"),
            .PPZ2 = getDoubleFromMap(rawParams(), "PPZ2"),
            .SSZ1 = getDoubleFromMap(rawParams(), "SSZ1"),
            .SSZ2 = getDoubleFromMap(rawParams(), "SSZ2"),
            .SSZ3 = getDoubleFromMap(rawParams(), "SSZ3"),
            .SSZ4 = getDoubleFromMap(rawParams(), "SSZ4")
        }),
    lambda(MF612ScalingFactors{
            .LFZO = getDoubleFromMap(rawParams(), "LFZO", 1.0),
            .LMUX = getDoubleFromMap(rawParams(), "LMUX", 1.0),
            .LMUY = getDoubleFromMap(rawParams(), "LMUY", 1.0),
            .LXAL = getDoubleFromMap(rawParams(), "LXAL", 1.0),
            .LMUV = getDoubleFromMap(rawParams(), "LMUV", 0.0), // Should default to 0 unless trying to simulate slip speed with decaying friction
            .LKX = getDoubleFromMap(rawParams(), "LKX", 1.0),
            .LKY = getDoubleFromMap(rawParams(), "LKY", 1.0),
            .LCX = getDoubleFromMap(rawParams(), "LCX", 1.0),
            .LCY = getDoubleFromMap(rawParams(), "LCY", 1.0),
            .LEX = getDoubleFromMap(rawParams(), "LEX", 1.0),
            .LEY = getDoubleFromMap(rawParams(), "LEY", 1.0),
            .LHX = getDoubleFromMap(rawParams(), "LHX", 1.0),
            .LHY = getDoubleFromMap(rawParams(), "LHY", 1.0),
            .LVX = getDoubleFromMap(rawParams(), "LVX", 1.0),
            .LVY = getDoubleFromMap(rawParams(), "LVY", 1.0),
            .LKYC = getDoubleFromMap(rawParams(), "LKYC", 1.0),
            .LKZC = getDoubleFromMap(rawParams(), "LKZC", 1.0),
            .LTR = getDoubleFromMap(rawParams(), "LTR", 1.0),
            .LRES = getDoubleFromMap(rawParams(), "LRES", 1.0),
            .LYKA = getDoubleFromMap(rawParams(), "LYKA", 1.0),
            .LVYKA = getDoubleFromMap(rawParams(), "LVYKA", 1.0),
            .LS = getDoubleFromMap(rawParams(), "LS", 1.0),
            .LMX = getDoubleFromMap(rawParams(), "LMX", 1.0),
            .LVMX = getDoubleFromMap(rawParams(), "LVMX", 1.0),
            .LMY = getDoubleFromMap(rawParams(), "LMY", 1.0)
        })
{
}

TireMF612::TireMF612(const MF612Params& params, const MF612ScalingFactors& scalingFactors)
    : t(params), lambda(scalingFactors)
{
}

inline double sgn(double x) {
    return (x > 0.0) - (x < 0.0);
}

TireForces TireMF612::evaluate(const TireInput& input) const {
    const double Fz = input.Fz;
    // Assumes user passes in alpha_star (4.E3 ~ alpha_star = std::tan(alpha) * sgn(Vcx))
    const double alpha_star = input.alpha;
    const double kappa = input.kappa;
    const double gamma = input.gamma;
    const double Vcx = input.Vcx;
    
    // All Constants
    const double Au = 10.0; // Suggested value = 10 (4.E8)

    // Fx Constants
    const double epsilonX = 0.1;
    const double zeta1 = 1.0;

    // Fy Constants
    const double epsilonK = 0.1;
    const double epsilonY = 0.1;
    const double zeta0 = 1.0;
    const double zeta2 = 1.0;
    const double zeta3 = 1.0;
    const double zeta4 = 1.0;

    // Mz constants
    const double zeta5 = 1.0;
    const double zeta6 = 1.0;
    const double zeta7 = 1.0;
    const double zeta8 = 1.0;

    // 4.E1
    const double FzoPrime = lambda.LFZO * t.FNOMIN;

    // 4.E2a
    const double dfz = (Fz - FzoPrime) / FzoPrime;

    // 4.E2b
    const double dpi = (t.INFLPRES - t.NOMPRES) / t.NOMPRES;

    // 4.E4
    const double gamma_star = std::sin(gamma);

    // 4.E6
    // const double epsilonV = 0.1;    // See 4.E6a, to prevent infinite values when velocity is 0
    // const double Vc = 1.0;  // Velocity magnitude of wheel contact patch center
    // const double Vcx = 1.0; // Contact patch center velocity in x direction
    // const double VcPrime = Vc + epsilonV;
    // const double cos_alpha = Vcx / VcPrime;
    const double cos_alpha = std::cos(alpha_star); // Assuming small angles, use above for large angles

    // 4.E7
    // TODO: Allow client to pass Vs and Vo if they want to model wet surfaces (friction decaying)
    const double Vs = 1.0; // Slip Velocity
    const double Vo = 1.0; // Reference velocity
    const double lamdaUxStar = lambda.LMUX / (1.0 + lambda.LMUV * (Vs / Vo));
    const double lamdaUyStar = lambda.LMUY / (1.0 + lambda.LMUV * (Vs / Vo));

    // 4.E8
    const double lamdaUxPrime = Au * lamdaUxStar / (1 + (Au - 1) * lamdaUxStar);
    const double lamdaUyPrime = Au * lamdaUyStar / (1 + (Au - 1) * lamdaUyStar);

    //
    // Longitudinal Force (Pure Longitudinal Slip, alpha = 0)
    // 

    // 4.E13
    const double ux = (t.PDX1 + t.PDX2 * dfz)
        * (1 + t.PPX3 * dpi + t.PPX4 * (dpi * dpi))
        * (1 - t.PDX3 * (gamma * gamma))
        * lamdaUxStar;

    // 4.E15
    const double Kxk = Fz * (t.PKX1 + t.PKX2 * dfz)
        * std::exp(t.PKX3 * dfz)
        * (1 + t.PPX1 * dpi + t.PPX2 * (dpi * dpi))
        * lambda.LKX;

    // 4.E11
    const double Cx = t.PCX1 * lambda.LCX;

    // 4.E12
    const double Dx = ux * Fz * zeta1;

    // 4.E16
    const double Bx = Kxk / (Cx * Dx + epsilonX);

    // 4.E17
    const double SHx = (t.PHX1 + t.PHX2 * dfz) * lambda.LHX;

    // 4.E10
    const double kx = kappa + SHx;

    // 4.E14
    const double Ex = (t.PEX1 + t.PEX2 * dfz + t.PEX3 * (dfz * dfz))
        * (1.0 - t.PEX4 * sgn(kx))
        * lambda.LEX;

    // 4.E18
    const double Svx = Fz * (t.PVX1 + t.PVX2 * dfz) * lambda.LVX * lamdaUxPrime * zeta1;

    // 4.E9
    const double Fxo = Dx * std::sin(Cx * std::atan(Bx * kx - Ex * (Bx * kx - std::atan(Bx * kx)))) + Svx;

    //
    // Lateral Force (Pure Side Slip, kappa = 0)
    // 

    // 4.E23
    const double uy = (t.PDY1 + t.PDY2 * dfz)
        * (1 + t.PPY3 * dpi + t.PPY4 * (dpi * dpi))
        * (1 - t.PDY3 * (gamma_star * gamma_star))
        * lamdaUyStar;

    // 4.E21
    const double Cy = t.PCY1 * lambda.LCY;

    // 4.E22
    const double Dy = uy * Fz * zeta2;

    // 4.E30
    const double Ky_gamma_o = Fz * (t.PKY6 + t.PKY7 * dfz) * (1 + t.PPY5 * dpi) * lambda.LKYC;

    // 4.E28
    const double Svy_gamma = Fz * (t.PVY3 + t.PVY4 * dfz) * gamma_star * lambda.LKYC * lamdaUyPrime * zeta2;

    // 4.E25
    const double Kya = t.PKY1 * FzoPrime
        * (1 + t.PPY1 * dpi)
        * (1 - t.PKY3 * std::abs(gamma_star))
        * std::sin(t.PKY4 * std::atan((Fz / FzoPrime) / ((t.PKY2 + t.PKY5 * (gamma_star * gamma_star)) * (1 + t.PPY2 * dpi))))
        * zeta3 * lambda.LKY;


    // 4.E39
    const double KyaPrime = Kya + epsilonK;

    // 4.E27
    const double Shy = (t.PHY1 + t.PHY2 * dfz) * lambda.LHY + ((Ky_gamma_o * gamma_star - Svy_gamma) / KyaPrime) * zeta0 + zeta4 - 1;

    // 4.E26
    const double By = Kya / (Cy * Dy + epsilonY);

    // 4.E20
    const double ay = alpha_star + Shy;

    // 4.E24
    const double Ey = (t.PEY1 + t.PEY2 * dfz)
        * (1 + t.PEY5 * (gamma_star * gamma_star) - (t.PEY3 + t.PEY4 * gamma_star) * sgn(ay))
        * lambda.LEY;

    // 4.E29
    const double Svy = Fz * (t.PVY1 + t.PVY2 * dfz) * lambda.LVY * lamdaUyPrime * zeta2 + Svy_gamma;

    // 4.E19
    const double Fyo = Dy * std::sin(Cy * std::atan(By * ay - Ey * (By * ay - std::atan(By * ay)))) + Svy;

    //
    // Aligning Torque (Pure Side Slip, kappa = 0)
    // 

    // 4.E47
    const double Dr = Fz * t.UNLOADED_RADIUS * (
        (t.QDZ6 + t.QDZ7 * dfz) * lambda.LRES * zeta2
        + ((t.QDZ8 + t.QDZ9 * dfz) * (1 + t.PPZ2 * dpi) + (t.QDZ10 + t.QDZ11 * dfz) * std::abs(gamma_star)) * gamma_star * lambda.LKZC * zeta0) * lamdaUyStar * sgn(Vcx) * cos_alpha + zeta8 - 1;

    // 4.E46
    const double Cr = zeta7;

    // 4.E45
    const double Br = (t.QBZ9 * lambda.LKY / lamdaUyStar + t.QBZ10 * By * Cy) * zeta6;

    // 4.E42
    const double Dto = Fz * (t.UNLOADED_RADIUS / FzoPrime) * (t.QDZ1 + t.QDZ2 * dfz) * (1 - t.PPZ1 * dpi) * lambda.LTR * sgn(Vcx);

    // 4.E43
    const double Dt = Dto * (1 + t.QDZ3 * std::abs(gamma_star) + t.QDZ4 * gamma_star * gamma_star) * zeta5;

    // 4.E41
    const double Ct = t.QCZ1;

    // 4.E40
    const double Bt = (t.QBZ1 + t.QBZ2 * dfz + t.QBZ3 * dfz * dfz) * (1 + t.QBZ4 * std::abs(gamma_star) + t.QBZ5 * gamma_star * gamma_star) * (lambda.LKY / lamdaUyStar);

    // 4.E38
    const double Shf = Shy + Svy / KyaPrime;

    // 4.E37
    const double alpha_r = alpha_star + Shf;

    // 4.E36
    // const double Mzro = Dr * std::cos(Cr * std::atan(Br * alpha_r)) * cos_alpha;

    // 4.E35
    const double Sht = t.QHZ1 + t.QHZ2 * dfz + (t.QHZ3 + t.QHZ4 * dfz) * gamma_star;

    // 4.E34
    const double alpha_t = alpha_star + Sht;

    // 4.E44
    const double Et = (t.QEZ1 + t.QEZ2 * dfz + t.QEZ3 * dfz * dfz) * (1 + (t.QEZ4 + t.QEZ5 * gamma_star) * (2 / std::numbers::pi) * std::atan(Bt * Ct * alpha_t));

    // 4.E33
    // const double to = Dt * std::cos(Ct * std::atan(Bt * alpha_t - Et * (Bt * alpha_t - std::atan(Bt * alpha_t)))) * cos_alpha;

    // 4.E32
    // const double MzoPrime = -to * Fyo;

    // 4.E31
    // const double Mzo = MzoPrime + Mzro;

    //
    // Longitudinal Force (Combined Slip)
    // 

    // 4.E57
    const double Shxa = t.RHX1;

    // 4.E56
    const double Exa = t.REX1 + t.REX2 * dfz;

    // 4.E55
    const double Cxa = t.RCX1;

    // 4.E54
    const double Bxa = (t.RBX1 + t.RBX3 * gamma_star * gamma_star) * std::cos(std::atan(t.RBX2 * kappa)) * lambda.LXAL;

    // 4.E53
    const double alpha_s = alpha_star + Shxa;

    // 4.E52
    const double Gxao = std::cos(Cxa * std::atan(Bxa * Shxa - Exa * (Bxa * Shxa - std::atan(Bxa * Shxa))));

    // 4.E51
    const double Gxa = std::cos(Cxa * std::atan(Bxa * alpha_s - Exa * (Bxa * alpha_s - std::atan(Bxa * alpha_s)))) / Gxao;

    // 4.E50
    const double Fx = Gxa * Fxo;

    //
    // Lateral Force (Combined Slip)
    // 

    // 4.E67
    const double Dvyk = uy * Fz * (t.RVY1 + t.RVY2 * dfz + t.RVY3 * gamma_star) * std::cos(std::atan(t.RVY4 * alpha_star)) * zeta2;

    // 4.E66
    const double Svyk = Dvyk * std::sin(t.RVY5 * std::atan(t.RVY6 * kappa)) * lambda.LVYKA;

    // 4.E65
    const double Shyk = t.RYH1 + t.RHY2 * dfz;

    // 4.E64
    const double Eyk = t.REY1 + t.REY2 * dfz;

    // 4.E63
    const double Cyk = t.RCY1;

    // 4.E62
    const double Byk = (t.RBY1 + t.RBY4 * gamma_star * gamma_star) * std::cos(std::atan(t.RBY2 * (alpha_star - t.RBY3))) * lambda.LYKA;

    // 4.E61
    const double kappa_s = kappa + Shyk;

    // 4.E60
    const double Gyko = std::cos(Cyk * std::atan(Byk * Shyk - Eyk * (Byk * Shyk - std::atan(Byk * Shyk))));

    // 4.E59
    const double Gyk = std::cos(Cyk * std::atan(Byk * kappa_s - Eyk * (Byk * kappa_s - std::atan(Byk * kappa_s)))) / Gyko;

    // 4.E58
    const double Fy = Gyk * Fyo + Svyk;

    //
    // Aligning Torque (Combined Slip)
    // 

    // 4.E78
    const double alpha_r_eq = std::sqrt(alpha_r * alpha_r + (Kxk / KyaPrime) * (Kxk / KyaPrime) * kappa * kappa) * sgn(alpha_r);

    // 4.E77
    const double alpha_t_eq = std::sqrt(alpha_t * alpha_t + (Kxk / KyaPrime) * (Kxk / KyaPrime) * kappa * kappa) * sgn(alpha_t);

    // 4.E76
    const double s = t.UNLOADED_RADIUS * (t.SSZ1 + t.SSZ2 * (Fy / FzoPrime) + (t.SSZ3 + t.SSZ4 * dfz) * gamma_star) * lambda.LS;

    // 4.E75
    const double Mzr = Dr * std::cos(Cr * std::atan(Br * alpha_r_eq)) * cos_alpha;

    // 4.E74
    const double FyPrime = Gyk * Fyo;

    // 4.E73
    const double t_pneumatic = Dt * std::cos(Ct * std::atan(Bt * alpha_t_eq - Et * (Bt * alpha_t_eq - std::atan(Bt * alpha_t_eq)))) * cos_alpha;

    // 4.E72
    const double MzPrime = -t_pneumatic * FyPrime;

    // 4.E71
    const double Mz = MzPrime + Mzr + s * Fx;

    return {
        .Fx = Fx,
        .Fy = Fy,
        .Mz = Mz
    };
}
