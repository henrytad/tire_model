#pragma once

namespace tire_model {

inline double sgn(double x) {
    return (x > 0.0) - (x < 0.0);
}

} // namespace tire_model
