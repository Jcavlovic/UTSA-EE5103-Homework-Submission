#include "Components.h"

#include <limits>

double Capacitor::resistance() const {
    return std::numeric_limits<double>::infinity();
}
