#include "Component.h"

#include <ostream>

double Component::voltageDrop(double current) const {
    return current * resistance();
}

double Component::power(double current) const {
    return current * current * resistance();
}

void Component::print(std::ostream& os) const {
    os << type() << "(" << label_ << " = " << value_ << ")";
}

std::ostream& operator<<(std::ostream& os, const Component& c) {
    c.print(os);
    return os;
}
