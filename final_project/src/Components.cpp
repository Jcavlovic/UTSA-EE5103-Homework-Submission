#include "Components.h"

#include <limits>

Complex Capacitor::impedance(double omega) const {
    if (omega == 0.0 || value_ == 0.0) {
        return Complex(std::numeric_limits<double>::infinity(), 0.0);
    }
    return Complex(0.0, -1.0 / (omega * value_));
}
