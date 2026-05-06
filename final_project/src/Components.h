#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Component.h"

class Resistor : public Component {
public:

    Resistor(std::string label, double ohms)
        : Component(std::move(label), ohms) {}

    Complex impedance(double omega) const override {
        (void)omega;
        return Complex(value_, 0.0);
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

    Complex impedance(double omega) const override;
    // Z = 1/(j*omega*C); returns infinity at omega=0 (DC open).

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

    Complex impedance(double omega) const override {
        return Complex(0.0, omega * value_);
    }

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

    Complex impedance(double omega) const override {
        (void)omega;
        return Complex(0.0, 0.0);
    }
    Complex voltageDrop(Complex current, double omega) const override {
        (void)current;
        (void)omega;
        return Complex(-value_, 0.0);
    }
    double power(Complex current, double omega) const override {
        (void)omega;
        return -value_ * std::real(current);
    }
    std::string type() const override {
        return "VoltageSource";
    }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<VoltageSource>(label_, value_);
    }
};

#endif
