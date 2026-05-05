#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>
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

    virtual std::complex<double> impedance(double omega) const = 0;
    /**
     * @brief Compute the complex impedance at a given angular frequency.
     * @param omega Angular frequency in rad/s.
     * @return Complex impedance Z(omega) in ohms.
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
