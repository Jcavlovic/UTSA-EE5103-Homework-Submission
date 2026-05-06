#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>
#include <iosfwd>
#include <memory>
#include <string>

using Complex = std::complex<double>;

class Component {
public:
Component(std::string label, double value)
        : label_(std::move(label)), value_(value) {}
    virtual ~Component() = default;

    virtual Complex impedance(double omega) const = 0;
    /**
     * @brief Complex impedance of the component at angular frequency omega.
     * @param omega Angular frequency in rad/s.
     * @return Z = R for a resistor, jwL for an inductor, 1/(jwC) for a
     *         capacitor (infinity at w=0), 0 for an ideal source/wire.
     */

    virtual Complex voltageDrop(Complex current, double omega) const;
    /**
     * @brief Phasor voltage drop across the component (V = I*Z).
     * @param current Phasor current through the component (RMS).
     * @param omega   Angular frequency in rad/s.
     */

    virtual double power(Complex current, double omega) const;
    /**
     * @brief Average real power dissipated by the component.
     *        For a passive element, P = |I|^2 * Re(Z) with I as RMS phasor.
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

      const std::string& label() const {
          /** @brief Get the component's label. */
        return label_;
    }

      double value() const {
          /** @brief Get the component's numeric value in SI units. */
        return value_;
    }

      friend std::ostream& operator<<(std::ostream& os, const Component& c);
      /** @brief Stream insertion operator; delegates to print(). */

protected:
    std::string label_;
    double value_;
};

#endif
