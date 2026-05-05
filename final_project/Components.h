#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Component.h"

// Concrete circuit elements: resistor, capacitor, inductor, voltage source.
// All inherit from Component and override impedance() with the appropriate
// frequency-domain expression.

class Resistor : public Component {
public:
    /**
     * @brief Construct a resistor.
     * @param label Identifier (e.g. "R1").
     * @param ohms Resistance in ohms.
     */
    Resistor(std::string label, double ohms)
        : Component(std::move(label), ohms) {}

    /**
     * @brief Resistor impedance: Z = R + j0 (frequency-independent).
     * @param omega Angular frequency in rad/s (unused).
     * @return Complex impedance in ohms.
     */
    std::complex<double> impedance(double omega) const override;
    std::string type() const override { return "Resistor"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Resistor>(label_, value_);
    }
};

class Capacitor : public Component {
public:
    /**
     * @brief Construct a capacitor.
     * @param label Identifier (e.g. "C1").
     * @param farads Capacitance in farads.
     */
    Capacitor(std::string label, double farads)
        : Component(std::move(label), farads) {}

    /**
     * @brief Capacitor impedance: Z = 1/(j*omega*C).
     * @param omega Angular frequency in rad/s; at omega=0 returns +infinity (open circuit).
     * @return Complex impedance in ohms.
     */
    std::complex<double> impedance(double omega) const override;
    std::string type() const override { return "Capacitor"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Capacitor>(label_, value_);
    }
};

class Inductor : public Component {
public:

    Inductor(std::string label, double henries)
        : Component(std::move(label), henries) {}

    std::complex<double> impedance(double omega) const override;
    std::string type() const override { return "Inductor"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Inductor>(label_, value_);
    }
};

class VoltageSource : public Component {
public:

    VoltageSource(std::string label, double volts)
        : Component(std::move(label), volts) {}

    std::complex<double> impedance(double omega) const override;
    std::string type() const override { return "VoltageSource"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<VoltageSource>(label_, value_);
    }
};

#endif
