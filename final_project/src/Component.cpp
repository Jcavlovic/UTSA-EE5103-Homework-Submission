#include "Component.h"

#include <ostream>

Complex Component::voltageDrop(Complex current, double omega) const {
    if (current == Complex(0.0, 0.0)) return Complex(0.0, 0.0);
    return current * impedance(omega);
}

double Component::power(Complex current, double omega) const {
    if (current == Complex(0.0, 0.0)) return 0.0;
    return std::norm(current) * std::real(impedance(omega));
}

void Component::print(std::ostream& os) const {
    os << type() << "(" << label_ << " = " << value_ << ")";
}

std::ostream& operator<<(std::ostream& os, const Component& c) {
    c.print(os);
    return os;
}
