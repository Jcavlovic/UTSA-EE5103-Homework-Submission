#include "Component.h"

#include <ostream>

void Component::print(std::ostream& os) const {
    os << type() << "(" << label_ << " = " << value_ << ")";
}

std::ostream& operator<<(std::ostream& os, const Component& c) {
    c.print(os);
    return os;
}
