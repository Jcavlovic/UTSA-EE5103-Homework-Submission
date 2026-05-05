#include "ComponentFactory.h"

#include "Components.h"

#include <stdexcept>

std::unique_ptr<Component> ComponentFactory::create(const std::string& type,
                                                    const std::string& label,
                                                    double value) {
    if (type == "Resistor")      
        return std::make_unique<Resistor>(label, value);
    if (type == "Capacitor")     
        return std::make_unique<Capacitor>(label, value);
    if (type == "Inductor")      
        return std::make_unique<Inductor>(label, value);
    if (type == "VoltageSource") 
        return std::make_unique<VoltageSource>(label, value);
    throw std::invalid_argument("Unknown component type: " + type);
}
