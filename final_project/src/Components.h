#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Component.h"

class Resistor : public Component {
public:

    Resistor(std::string label, double ohms)
        : Component(std::move(label), ohms) {}

    double resistance() const override { 
        return value_; 
    }
    std::string type() const override { 
        return "Resistor"; 
    }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Resistor>(label_, value_);
    }
};

class Capacitor : public Component {
public:

    Capacitor(std::string label, double farads)
        : Component(std::move(label), farads) {}

    double resistance() const override;

    double voltageDrop(double current) const override { 
        (void)current; 
        return 0.0; 
    }
    double power(double current) const override { 
        (void)current; 
        return 0.0; 
    }

    std::string type() const override { 
        return "Capacitor"; 
    }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Capacitor>(label_, value_);
    }
};

class Inductor : public Component {
public:
    Inductor(std::string label, double henries)
        : Component(std::move(label), henries) {}

    double resistance() const override { 
        return 0.0; 
    }
    double voltageDrop(double current) const override { 
        (void)current; 
        return 0.0; }
    double power(double current) const override { 
        (void)current; 
        return 0.0; }

    std::string type() const override { 
        return "Inductor"; 
    }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Inductor>(label_, value_);
    }
};

class VoltageSource : public Component {
public:
    VoltageSource(std::string label, double volts)
        : Component(std::move(label), volts) {}

    double resistance() const override { 
        return 0.0; 
    }
    double voltageDrop(double current) const override { 
        (void)current; 
        return -value_; 
    }
    double power(double current) const override { 
        return -value_ * current; 
    }
    std::string type() const override { 
        return "VoltageSource"; 
    }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<VoltageSource>(label_, value_);
    }
};

#endif
