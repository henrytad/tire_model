#include "pac2002/tire_pac2002.hpp"
#include "tire_file_parser.hpp"
#include "math_utils.hpp"

#include <cmath>
#include <numbers>
#include <utility>

using namespace tire_model;

TirePAC2002::TirePAC2002(std::map<std::string, std::string> params)
    : TireModelBase(std::move(params))
    , t(PAC2002Params{
            .LENGTH = getStringFromMap(rawParams(), "LENGTH"),
            .FORCE = getStringFromMap(rawParams(), "FORCE"),
            .UNLOADED_RADIUS = getDoubleFromMap(rawParams(), "UNLOADED_RADIUS"),
            .FNOMIN = getDoubleFromMap(rawParams(), "FNOMIN"),
            .VERTICAL_STIFFNESS = getDoubleFromMap(rawParams(), "VERTICAL_STIFFNESS"),

            // Pure longitudinal
            .PCX1 = getDoubleFromMap(rawParams(), "PCX1"),
            .PDX1 = getDoubleFromMap(rawParams(), "PDX1"),
            .PDX2 = getDoubleFromMap(rawParams(), "PDX2"),
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

            // Longitudinal combined
            .RBX1 = getDoubleFromMap(rawParams(), "RBX1"),
            .RBX2 = getDoubleFromMap(rawParams(), "RBX2"),
            .RBX3 = getDoubleFromMap(rawParams(), "RBX3"),
            .RCX1 = getDoubleFromMap(rawParams(), "RCX1"),
            .REX1 = getDoubleFromMap(rawParams(), "REX1"),
            .REX2 = getDoubleFromMap(rawParams(), "REX2"),
            .RHX1 = getDoubleFromMap(rawParams(), "RHX1"),

            // Pure lateral
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
            .PKY4 = getDoubleFromMap(rawParams(), "PKY4", 2.0), // Default to 2.0 from (4.E25)
            .PKY5 = getDoubleFromMap(rawParams(), "PKY5"),
            .PKY6 = getDoubleFromMap(rawParams(), "PKY6"),
            .PKY7 = getDoubleFromMap(rawParams(), "PKY7"),
            .PHY1 = getDoubleFromMap(rawParams(), "PHY1"),
            .PHY2 = getDoubleFromMap(rawParams(), "PHY2"),
            .PVY1 = getDoubleFromMap(rawParams(), "PVY1"),
            .PVY2 = getDoubleFromMap(rawParams(), "PVY2"),
            .PVY3 = getDoubleFromMap(rawParams(), "PVY3"),
            .PVY4 = getDoubleFromMap(rawParams(), "PVY4"),

            // Lateral combined
            .RBY1 = getDoubleFromMap(rawParams(), "RBY1"),
            .RBY2 = getDoubleFromMap(rawParams(), "RBY2"),
            .RBY3 = getDoubleFromMap(rawParams(), "RBY3"),
            .RBY4 = getDoubleFromMap(rawParams(), "RBY4"),
            .RCY1 = getDoubleFromMap(rawParams(), "RCY1"),
            .REY1 = getDoubleFromMap(rawParams(), "REY1"),
            .REY2 = getDoubleFromMap(rawParams(), "REY2"),
            .RHY1 = getDoubleFromMap(rawParams(), "RHY1"),
            .RHY2 = getDoubleFromMap(rawParams(), "RHY2"),
            .RVY1 = getDoubleFromMap(rawParams(), "RVY1"),
            .RVY2 = getDoubleFromMap(rawParams(), "RVY2"),
            .RVY3 = getDoubleFromMap(rawParams(), "RVY3"),
            .RVY4 = getDoubleFromMap(rawParams(), "RVY4"),
            .RVY5 = getDoubleFromMap(rawParams(), "RVY5"),
            .RVY6 = getDoubleFromMap(rawParams(), "RVY6"),

            // Aligning torque
            .QBZ1 = getDoubleFromMap(rawParams(), "QBZ1"),
            .QBZ2 = getDoubleFromMap(rawParams(), "QBZ2"),
            .QBZ3 = getDoubleFromMap(rawParams(), "QBZ3"),
            .QBZ5 = getDoubleFromMap(rawParams(), "QBZ5"),
            .QBZ6 = getDoubleFromMap(rawParams(), "QBZ6"),
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

            // Combined-slip aligning torque
            .SSZ1 = getDoubleFromMap(rawParams(), "SSZ1"),
            .SSZ2 = getDoubleFromMap(rawParams(), "SSZ2"),
            .SSZ3 = getDoubleFromMap(rawParams(), "SSZ3"),
            .SSZ4 = getDoubleFromMap(rawParams(), "SSZ4")
        })
    , lambda(PAC2002ScalingFactors{
            .LFZO = getDoubleFromMap(rawParams(), "LFZO", 1.0),
            .LMUX = getDoubleFromMap(rawParams(), "LMUX", 1.0),
            .LMUY = getDoubleFromMap(rawParams(), "LMUY", 1.0),
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
            .LXAL = getDoubleFromMap(rawParams(), "LXAL", 1.0),
            .LYKA = getDoubleFromMap(rawParams(), "LYKA", 1.0),
            .LVYKA = getDoubleFromMap(rawParams(), "LVYKA", 1.0),
            .LS = getDoubleFromMap(rawParams(), "LS", 1.0)
        })
{
}

TirePAC2002::TirePAC2002(const PAC2002Params& params, const PAC2002ScalingFactors& scalingFactors)
    : t(params), lambda(scalingFactors)
{
}

// Source: Pacejka, Tire and Vehicle Dynamics, 2nd ed., Elsevier, 2006, Magic Formula tire model equations.
TireForces TirePAC2002::evaluate(const TireInput& input) const {
    const double Fz = input.Fz;
    // Assumes user passes in alpha_star (4.E3 ~ alpha_star = std::tan(alpha) * sgn(Vcx))
    const double alpha_star = input.alpha;
    const double kappa = input.kappa;
    const double gamma = input.gamma;
    const double Vcx = input.Vcx;

    // -------------------------------------------------------------------------
    // Constants / singularity protection
    // -------------------------------------------------------------------------
    const double gx = 1e-6;
    const double gy = 1e-6;
    const double gK = 1e-6;
    const double gVx = 1e-6;

    const double zeta0 = 1.0;
    const double zeta1 = 1.0;
    const double zeta2 = 1.0;
    const double zeta3 = 1.0;
    const double zeta4 = 1.0;
    const double zeta5 = 1.0;
    const double zeta6 = 1.0;
    const double zeta7 = 1.0;
    const double zeta8 = 1.0;

    // -------------------------------------------------------------------------
    // Base quantities
    // -------------------------------------------------------------------------

    // (4.E1)
    const double FzoPrime = lambda.LFZO * t.FNOMIN;

    // (4.E2a)
    const double dfz = (Fz - FzoPrime) / FzoPrime;

    // (4.E4)
    const double gamma_star = std::sin(gamma);

    // (4.E6)
    const double cos_alpha = std::cos(alpha_star);

    // -------------------------------------------------------------------------
    // Longitudinal force - pure slip
    // -------------------------------------------------------------------------

    // (4.E13)
    const double mux = (t.PDX1 + t.PDX2 * dfz) * lambda.LMUX;

    // (4.E15)
    const double Kxk = Fz * (t.PKX1 + t.PKX2 * dfz) * std::exp(t.PKX3 * dfz) * lambda.LKX;

    // (4.E11)
    const double Cx = t.PCX1 * lambda.LCX;

    // (4.E12)
    const double Dx = mux * Fz * zeta1;

    // (4.E17)
    const double SHx = (t.PHX1 + t.PHX2 * dfz) * lambda.LHX;

    // (4.E10)
    const double kx = kappa + SHx;

    // (4.E14)
    const double Ex = (t.PEX1 + t.PEX2 * dfz + t.PEX3 * dfz * dfz)
        * (1.0 - t.PEX4 * sgn(kx))
        * lambda.LEX;

    // (4.E16)
    const double Bx = Kxk / (Cx * Dx + gx);

    // (4.E18)
    // NOTE: PAC2002 low-speed factor uses |Vcx| / (gVx + |Vcx|)
    const double Svx = Fz * (t.PVX1 + t.PVX2 * dfz)
        * (std::abs(Vcx) / (gVx + std::abs(Vcx)))
        * lambda.LVX
        * lambda.LMUX
        * zeta1;

    // (4.E9)
    const double Fxo =
        Dx * std::sin(Cx * std::atan(Bx * kx - Ex * (Bx * kx - std::atan(Bx * kx)))) + Svx;

    // -------------------------------------------------------------------------
    // Lateral force - pure slip
    // -------------------------------------------------------------------------

    // (4.E23)
    const double muy = (t.PDY1 + t.PDY2 * dfz) * (1.0 - t.PDY3 * gamma_star * gamma_star) * lambda.LMUY;

    // (4.E21)
    const double Cy = t.PCY1 * lambda.LCY;

    // (4.E22)
    const double Dy = muy * Fz * zeta2;

    // (4.E25)
    const double Kya = t.PKY1 * FzoPrime
        * std::sin(std::atan((Fz / FzoPrime) / (t.PKY2 + t.PKY5 * gamma_star * gamma_star)) * t.PKY4)
        * (1.0 - t.PKY3 * std::abs(gamma_star))
        * zeta3
        * lambda.LKY;

    // (4.E39)
    const double KyaPrime = Kya + gK;

    // (4.E30)
    const double Kygamma0 = Fz * (t.PKY6 + t.PKY7 * dfz) * lambda.LKYC;

    // (4.E28)
    const double Svygamma = Fz * (t.PVY3 + t.PVY4 * dfz) * gamma_star * lambda.LKYC * lambda.LMUY * zeta2;

    // (4.E27)
    const double SHy =
        (t.PHY1 + t.PHY2 * dfz) * lambda.LHY
        + ((Kygamma0 * gamma_star - Svygamma) * zeta0) / KyaPrime
        + zeta4 - 1.0;

    // (4.E20)
    const double ay = alpha_star + SHy;

    // (4.E24)
    const double Ey =
        (t.PEY1 + t.PEY2 * dfz)
        * (1.0 + t.PEY5 * gamma_star * gamma_star
           - (t.PEY3 + t.PEY4 * gamma_star) * sgn(ay))
        * lambda.LEY;

    // (4.E26)
    const double By = Kya / (Cy * Dy + gy);

    // (4.E29)
    const double Svy =
        Fz * (t.PVY1 + t.PVY2 * dfz) * lambda.LVY * lambda.LMUY * zeta2 + Svygamma;

    // (4.E19)
    const double Fyo =
        Dy * std::sin(Cy * std::atan(By * ay - Ey * (By * ay - std::atan(By * ay)))) + Svy;

    // -------------------------------------------------------------------------
    // Aligning torque - pure side slip
    // -------------------------------------------------------------------------

    // (4.E35)
    const double SHt = t.QHZ1 + t.QHZ2 * dfz + (t.QHZ3 + t.QHZ4 * dfz) * gamma_star;

    // (4.E34)
    const double alpha_t = alpha_star + SHt;

    // (4.E38)
    const double SHf = SHy + Svy / KyaPrime;

    // (4.E37)
    const double alpha_r = alpha_star + SHf;

    // (4.E40)
    // Note: PAC2002 steady-state set uses QBZ5 and QBZ6 here
    const double Bt =
        (t.QBZ1 + t.QBZ2 * dfz + t.QBZ3 * dfz * dfz)
        * (1.0 + t.QBZ5 * std::abs(gamma_star) + t.QBZ6 * gamma_star * gamma_star)
        * (lambda.LKY / lambda.LMUY);

    // (4.E41)
    const double Ct = t.QCZ1;

    // (4.E42)
    const double Dto =
        Fz * (t.UNLOADED_RADIUS / FzoPrime) * (t.QDZ1 + t.QDZ2 * dfz) * lambda.LTR * sgn(Vcx);

    // (4.E43)
    const double Dt = Dto * (1.0 + t.QDZ3 * std::abs(gamma_star) + t.QDZ4 * gamma_star * gamma_star) * zeta5;

    // (4.E44)
    const double Et =
        (t.QEZ1 + t.QEZ2 * dfz + t.QEZ3 * dfz * dfz)
        * (1.0 + (t.QEZ4 + t.QEZ5 * gamma_star) * (2.0 / std::numbers::pi) * std::atan(Bt * Ct * alpha_t));

    // (4.E45)
    const double Br = (t.QBZ9 * (lambda.LKY / lambda.LMUY) + t.QBZ10 * By * Cy) * zeta6;

    // (4.E46)
    const double Cr = zeta7;

    // (4.E47)
    const double Dr =
        Fz * t.UNLOADED_RADIUS
        * (((t.QDZ6 + t.QDZ7 * dfz) * lambda.LRES * zeta2)
           + ((t.QDZ8 + t.QDZ9 * dfz) * gamma_star * lambda.LKZC * zeta0)
           + ((t.QDZ10 + t.QDZ11 * dfz) * gamma_star * std::abs(gamma_star) * zeta0))
        * cos_alpha
        * lambda.LMUY
        * sgn(Vcx)
        + zeta8 - 1.0;

    // -------------------------------------------------------------------------
    // Longitudinal force - combined slip
    // -------------------------------------------------------------------------

    // (4.E57)
    const double SHxa = t.RHX1;

    // (4.E53)
    const double alpha_s = alpha_star + SHxa;

    // (4.E56)
    const double Exa = t.REX1 + t.REX2 * dfz;

    // (4.E55)
    const double Cxa = t.RCX1;

    // (4.E54)
    const double Bxa =
        (t.RBX1 + t.RBX3 * gamma_star * gamma_star)
        * std::cos(std::atan(t.RBX2 * kappa))
        * lambda.LXAL;

    // (4.E52)
    const double Gxao =
        std::cos(Cxa * std::atan(Bxa * SHxa - Exa * (Bxa * SHxa - std::atan(Bxa * SHxa))));

    // (4.E51)
    const double Gxa =
        std::cos(Cxa * std::atan(Bxa * alpha_s - Exa * (Bxa * alpha_s - std::atan(Bxa * alpha_s))))
        / Gxao;

    // (4.E50)
    const double Fx = Gxa * Fxo;

    // -------------------------------------------------------------------------
    // Lateral force - combined slip
    // -------------------------------------------------------------------------

    // (4.E65)
    const double SHyk = t.RHY1 + t.RHY2 * dfz;

    // (4.E61)
    const double kappa_s = kappa + SHyk;

    // (4.E64)
    const double Eyk = t.REY1 + t.REY2 * dfz;

    // (4.E63)
    const double Cyk = t.RCY1;

    // (4.E62)
    const double Byk =
        (t.RBY1 + t.RBY4 * gamma_star * gamma_star)
        * std::cos(std::atan(t.RBY2 * (alpha_star - t.RBY3)))
        * lambda.LYKA;

    // (4.E60)
    const double Gyko =
        std::cos(Cyk * std::atan(Byk * SHyk - Eyk * (Byk * SHyk - std::atan(Byk * SHyk))));

    // (4.E59)
    const double Gyk =
        std::cos(Cyk * std::atan(Byk * kappa_s - Eyk * (Byk * kappa_s - std::atan(Byk * kappa_s))))
        / Gyko;

    // (4.E67)
    const double Dvyk =
        muy * Fz
        * (t.RVY1 + t.RVY2 * dfz + t.RVY3 * gamma_star)
        * std::cos(std::atan(t.RVY4 * alpha_star))
        * zeta2;

    // (4.E66)
    const double Svyk =
        Dvyk * std::sin(t.RVY5 * std::atan(t.RVY6 * kappa)) * lambda.LVYKA;

    // (4.E58)
    const double Fy = Gyk * Fyo + Svyk;

    // -------------------------------------------------------------------------
    // Aligning torque - combined slip
    // -------------------------------------------------------------------------

    // (4.E77)
    const double alpha_t_eq =
        std::sqrt(alpha_t * alpha_t + std::pow((Kxk / KyaPrime) * kappa, 2.0)) * sgn(alpha_t);

    // (4.E78)
    const double alpha_r_eq =
        std::sqrt(alpha_r * alpha_r + std::pow((Kxk / KyaPrime) * kappa, 2.0)) * sgn(alpha_r);

    // (4.E76)
    const double s =
        t.UNLOADED_RADIUS
        * (t.SSZ1 + t.SSZ2 * (Fy / FzoPrime) + (t.SSZ3 + t.SSZ4 * dfz) * gamma_star)
        * lambda.LS;

    // (4.E75)
    const double Mzr = Dr * std::cos(Cr * std::atan(Br * alpha_r_eq));

    // (4.E74)
    const double FyPrime = Fy - Svyk;

    // (4.E73)
    const double t_p =
        Dt * std::cos(Ct * std::atan(Bt * alpha_t_eq - Et * (Bt * alpha_t_eq - std::atan(Bt * alpha_t_eq))))
        * cos_alpha;

    // (4.E72)
    const double MzPrime = -t_p * FyPrime;

    // (4.E71)
    const double Mz = MzPrime + Mzr + s * Fx;

    return {
        .Fx = Fx,
        .Fy = Fy,
        .Mz = Mz
    };
}