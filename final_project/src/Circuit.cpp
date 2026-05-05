#include "Circuit.h"

#include "ComponentFactory.h"

#include <cmath>
#include <fstream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>

double Circuit::resistance() const {
    if (topology_ == Topology::Series) {
        double R = 0.0;
        for (const auto& e : elements_) {
            double Re = e->resistance();
            if (std::isinf(Re)) return std::numeric_limits<double>::infinity();
            R += Re;
        }
        return R;
    }

    double sumG = 0.0;
    for (const auto& e : elements_) {
        double Re = e->resistance();
        if (Re == 0.0) return 0.0;
        if (std::isinf(Re)) continue;
        sumG += 1.0 / Re;
    }
    if (sumG == 0.0) return std::numeric_limits<double>::infinity();
    return 1.0 / sumG;
}

void Circuit::analyze(std::ostream& os, double sourceVoltage, int indent) const {
    const std::string pad(indent, ' ');
    const double R = resistance();
    os << pad << "Total resistance: " << R << " ohm\n";

    if (topology_ == Topology::Series) {
        const double I = std::isinf(R) ? 0.0 : sourceVoltage / R;
        os << pad << "Applied: " << sourceVoltage << " V, current: " << I << " A\n";
        for (const auto& e : elements_) {
            const double v = e->voltageDrop(I);
            const double p = e->power(I);
            os << pad << "  " << *e
               << "  V_drop = " << v << " V,  P = " << p << " W\n";
            if (auto* sub = dynamic_cast<const Circuit*>(e.get())) {
                sub->analyze(os, v, indent + 4);
            }
        }
    } else {
        os << pad << "Applied: " << sourceVoltage << " V across all branches\n";
        double totalI = 0.0;
        for (const auto& e : elements_) {
            const double Re = e->resistance();
            const double Ib = (Re > 0.0 && std::isfinite(Re))
                                ? sourceVoltage / Re
                                : 0.0;
            const double p = e->power(Ib);
            os << pad << "  " << *e
               << "  I = " << Ib << " A,  P = " << p << " W\n";
            totalI += Ib;
            if (auto* sub = dynamic_cast<const Circuit*>(e.get())) {
                sub->analyze(os, sourceVoltage, indent + 4);
            }
        }
        os << pad << "Total current: " << totalI << " A\n";
    }

    const double pTot = (R > 0.0 && std::isfinite(R))
                            ? sourceVoltage * sourceVoltage / R
                            : 0.0;
    os << pad << "Total power dissipated: " << pTot << " W\n";
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
