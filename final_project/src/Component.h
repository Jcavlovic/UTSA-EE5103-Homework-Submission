#ifndef COMPONENT_H
#define COMPONENT_H

#include <iosfwd>
#include <memory>
#include <string>


class Component {
public:
Component(std::string label, double value)
/**
 * @brief Construct a component with an identifying label and a numeric value.
 * @param label Human-readable identifier (e.g. "R1").
 * @param value Component value in SI units (ohms, henries, farads, volts).
 */
        : label_(std::move(label)), value_(value) {}
    virtual ~Component() = default;

    virtual double resistance() const = 0;
    /**
     * @brief DC resistance of the component in ohms.
     * @return 0 for an ideal wire/inductor/source, +infinity for an open
     *         (capacitor at DC steady state), R for a resistor.
     */

    virtual double voltageDrop(double current) const;
    /**
     * @brief Voltage drop across the component for a given current (V = I*R).
     * @param current Current through the component in amperes.
     * @return Voltage drop in volts.
     */

    virtual double power(double current) const;
    /**
     * @brief Power dissipated by the component (P = I^2 * R).
     * @param current Current through the component in amperes.
     * @return Power in watts.
     */

     virtual std::string type() const = 0;
     /** @brief Return the type name of the component (e.g. "Resistor"). */

     virtual std::unique_ptr<Component> clone() const = 0;
     /** @brief Produce a deep copy of this component. */

     virtual void print(std::ostream& os) const;
     /**
      * @brief Write a human-readable representation to a stream.
      * @param os Output stream to write to.
      */

      const std::string& label() const { return label_; }
      /** @brief Get the component's label. */

      double value() const { return value_; }
      /** @brief Get the component's numeric value in SI units. */

      friend std::ostream& operator<<(std::ostream& os, const Component& c);
      /** @brief Stream insertion operator; delegates to print(). */

protected:
    std::string label_;
    double value_;
};

#endif
