#include "Circuit.h"

#include "ComponentFactory.h"

#include <cmath>
#include <fstream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr Complex kZero(0.0, 0.0);
constexpr Complex kOne(1.0, 0.0);

inline bool isInfMag(Complex z) {
    return std::isinf(std::abs(z));
}
inline double rad2deg(double r) {
    return r * 180.0 / kPi;
}
}

Complex Circuit::impedance(double omega) const {
    if (topology_ == Topology::Series) {
        Complex Z = kZero;
        for (const auto& e : elements_) {
            Complex Ze = e->impedance(omega);
            if (isInfMag(Ze))
                return Complex(std::numeric_limits<double>::infinity(), 0.0);
            Z += Ze;
        }
        return Z;
    }

    Complex sumY = kZero;
    for (const auto& e : elements_) {
        Complex Ze = e->impedance(omega);
        if (Ze == kZero) return kZero;
        if (isInfMag(Ze)) continue;
        sumY += kOne / Ze;
    }
    if (sumY == kZero)
        return Complex(std::numeric_limits<double>::infinity(), 0.0);
    return kOne / sumY;
}

void Circuit::analyze(std::ostream& os, double sourceVoltage, double omega, int indent) const {
    const std::string pad(indent, ' ');
    const Complex Z = impedance(omega);
    const double magZ = std::abs(Z);

    os << pad << "Total impedance: |Z| = " << magZ
       << " ohm, angle = " << rad2deg(std::arg(Z)) << " deg"
       << "  (Z = " << std::real(Z) << " + j" << std::imag(Z) << ")\n";

    if (topology_ == Topology::Series) {
        const Complex Vsrc(sourceVoltage, 0.0);
        const Complex I = isInfMag(Z) ? kZero : Vsrc / Z;
        os << pad << "Applied: " << sourceVoltage << " V (RMS, 0 deg), omega = "
           << omega << " rad/s\n";
        os << pad << "Current: |I| = " << std::abs(I)
           << " A, angle = " << rad2deg(std::arg(I)) << " deg\n";
        for (const auto& e : elements_) {
            const Complex v = e->voltageDrop(I, omega);
            const double p = e->power(I, omega);
            os << pad << "  " << *e
               << "  |V| = " << std::abs(v) << " V ("
               << rad2deg(std::arg(v)) << " deg),  P = " << p << " W\n";
            if (auto* sub = dynamic_cast<const Circuit*>(e.get())) {
                sub->analyze(os, std::abs(v), omega, indent + 4);
            }
        }
    } else {
        os << pad << "Applied: " << sourceVoltage << " V across all branches, omega = "
           << omega << " rad/s\n";
        Complex totalI = kZero;
        for (const auto& e : elements_) {
            const Complex Ze = e->impedance(omega);
            const Complex Ib = (Ze != kZero && !isInfMag(Ze))
                                ? Complex(sourceVoltage, 0.0) / Ze
                                : kZero;
            const double p = e->power(Ib, omega);
            os << pad << "  " << *e
               << "  |I| = " << std::abs(Ib) << " A ("
               << rad2deg(std::arg(Ib)) << " deg),  P = " << p << " W\n";
            totalI += Ib;
            if (auto* sub = dynamic_cast<const Circuit*>(e.get())) {
                sub->analyze(os, sourceVoltage, omega, indent + 4);
            }
        }
        os << pad << "Total current: |I| = " << std::abs(totalI)
           << " A, angle = " << rad2deg(std::arg(totalI)) << " deg\n";
    }

    const double pTot = (magZ > 0.0 && std::isfinite(magZ))
                            ? sourceVoltage * sourceVoltage * std::real(kOne / Z)
                            : 0.0;
    os << pad << "Total real power dissipated: " << pTot << " W\n";
}

std::unique_ptr<Component> Circuit::clone() const {
    auto copy = std::make_unique<Circuit>(topology_, label_);
    for (const auto& e : elements_) {
        copy->add(e->clone());
    }
    return copy;
}

void Circuit::print(std::ostream& os) const {
    os << "Circuit '" << label_ << "' ("
       << (topology_ == Topology::Series ? "series" : "parallel")
       << ", " << elements_.size() << " elements)";
}

Circuit Circuit::operator+(const Circuit& rhs) const {
    Circuit r(Topology::Series, label_ + " + " + rhs.label_);
    r.add(this->clone());
    r.add(rhs.clone());
    return r;
}

Circuit Circuit::operator*(const Circuit& rhs) const {
    Circuit r(Topology::Parallel, label_ + " * " + rhs.label_);
    r.add(this->clone());
    r.add(rhs.clone());
    return r;
}

void Circuit::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open file: " + filename);

    out << (topology_ == Topology::Series ? "SERIES" : "PARALLEL")
        << " " << label_ << "\n";
    for (const auto& e : elements_) {
        out << e->type() << " " << e->label() << " " << e->value() << "\n";
    }
}

Circuit Circuit::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Cannot open file: " + filename);

    std::string topoTag, label;
    in >> topoTag >> label;
    Topology topo = (topoTag == "SERIES") ? Topology::Series : Topology::Parallel;
    Circuit c(topo, label);

    std::string type;
    double value;
    while (in >> type >> label >> value) {
        c.add(ComponentFactory::create(type, label, value));
    }
    return c;
}
