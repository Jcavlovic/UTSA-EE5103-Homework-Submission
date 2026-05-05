#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Component.h"

// Concrete circuit elements: resistor, capacitor, inductor, voltage source.
// All inherit from Component. Behavior is given for DC steady state:
//   Resistor  : R = value
//   Inductor  : R = 0   (acts as a wire)
//   Capacitor : R = inf (acts as an open circuit, blocks DC)
//   VoltageSource : R = 0 (ideal source has no internal resistance)

class Resistor : public Component {
public:
    /**
     * @brief Construct a resistor.
     * @param label Identifier (e.g. "R1").
     * @param ohms Resistance in ohms.
     */
    Resistor(std::string label, double ohms)
        : Component(std::move(label), ohms) {}

    double resistance() const override { return value_; }
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

    /** @brief At DC steady state a capacitor is an open circuit. */
    double resistance() const override;
    /** @brief No current flows through an ideal capacitor at DC steady state. */
    double voltageDrop(double current) const override { (void)current; return 0.0; }
    double power(double current) const override { (void)current; return 0.0; }

    std::string type() const override { return "Capacitor"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Capacitor>(label_, value_);
    }
};

class Inductor : public Component {
public:
    Inductor(std::string label, double henries)
        : Component(std::move(label), henries) {}

    /** @brief At DC steady state an inductor behaves as a perfect wire. */
    double resistance() const override { return 0.0; }
    double voltageDrop(double current) const override { (void)current; return 0.0; }
    double power(double current) const override { (void)current; return 0.0; }

    std::string type() const override { return "Inductor"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<Inductor>(label_, value_);
    }
};

class VoltageSource : public Component {
public:
    VoltageSource(std::string label, double volts)
        : Component(std::move(label), volts) {}

    /** @brief Ideal voltage source: zero internal resistance. */
    double resistance() const override { return 0.0; }
    /** @brief A source raises potential; report the EMF as a negative drop. */
    double voltageDrop(double current) const override { (void)current; return -value_; }
    /** @brief Power supplied by the source equals -V * I (negative = sourced). */
    double power(double current) const override { return -value_ * current; }

    std::string type() const override { return "VoltageSource"; }
    std::unique_ptr<Component> clone() const override {
        return std::make_unique<VoltageSource>(label_, value_);
    }
};

#endif
