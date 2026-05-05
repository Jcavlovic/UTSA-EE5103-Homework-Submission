#include "Components.h"

#include <limits>

std::complex<double> Resistor::impedance(double) const {

    return {value_, 0.0};
}

std::complex<double> Capacitor::impedance(double omega) const {

    if (omega == 0.0) {
        return {std::numeric_limits<double>::infinity(), 0.0};
    }
    return {0.0, -1.0 / (omega * value_)};
}

std::complex<double> Inductor::impedance(double omega) const {
    return {0.0, omega * value_};
}

std::complex<double> VoltageSource::impedance(double) const {
    return {0.0, 0.0};
}
