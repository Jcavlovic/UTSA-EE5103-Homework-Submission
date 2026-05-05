#include "Circuit.h"

#include "ComponentFactory.h"

#include <cmath>
#include <fstream>
#include <numeric>
#include <ostream>
#include <stdexcept>

using cplx = std::complex<double>;

std::complex<double> Circuit::impedance(double omega) const {
    if (topology_ == Topology::Series) {
        return std::accumulate(
            elements_.begin(), elements_.end(), cplx(0.0, 0.0),
            [omega](const cplx& acc, const std::unique_ptr<Component>& e) {
                return acc + e->impedance(omega);
            });
    }

    cplx sumY(0.0, 0.0);
    for (const auto& e : elements_) {
        cplx z = e->impedance(omega);
        if (std::isinf(z.real())) continue;
        sumY += cplx(1.0, 0.0) / z;
    }
    return cplx(1.0, 0.0) / sumY;
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
