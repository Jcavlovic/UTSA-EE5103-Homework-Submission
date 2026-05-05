#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

class Circuit : public Component {
public:
    enum class Topology { Series, Parallel };

    Circuit(Topology topology = Topology::Series, std::string label = "circuit")
        : Component(std::move(label), 0.0), topology_(topology) {}


    void add(std::unique_ptr<Component> c) {
        elements_.push_back(std::move(c));
    }

    const std::vector<std::unique_ptr<Component>>& elements() const {
        /** @brief Read-only access to the list of child components. */
        return elements_;
    }

    std::size_t size() const {
        /** @brief Number of child components. */
        return elements_.size();
    }

    Topology topology() const {
        /** @brief Wiring topology (series or parallel). */
        return topology_;
    }

    double resistance() const override;
    /**
     * @brief Equivalent DC resistance of the circuit.
     * @return Sum of child resistances (series) or 1/sum(1/R_i) (parallel).
     */

    void analyze(std::ostream& os, double sourceVoltage, int indent = 2) const;
    /**
     * @brief Print a DC analysis: total R, current, per-component voltage
     *        drop and power dissipated.
     * @param os             Output stream.
     * @param sourceVoltage  Source voltage applied across the circuit (V).
     * @param indent         Leading spaces for nested sub-circuits.
     */

    std::string type() const override {
        return "Circuit";
    }

    std::unique_ptr<Component> clone() const override;
    /** @brief Deep copy of the circuit, including all child components. */

    void print(std::ostream& os) const override;
    /**
     * @brief Print the circuit header (label, topology, element count).
     * @param os Output stream.
     */

    Circuit operator+(const Circuit& rhs) const;
    /**
     * @brief Combine two circuits in series.
     * @param rhs Right-hand-side circuit.
     * @return New series circuit containing clones of both operands.
     */

    Circuit operator*(const Circuit& rhs) const;
    /**
     * @brief Combine two circuits in parallel.
     * @param rhs Right-hand-side circuit.
     * @return New parallel circuit containing clones of both operands.
     */

    void save(const std::string& filename) const;
    /**
     * @brief Serialize the circuit (flat, one level deep) to a text file.
     * @param filename Path to write to.
     * @throws std::runtime_error if the file cannot be opened.
     */

    static Circuit load(const std::string& filename);
    /**
     * @brief Load a previously saved circuit from a text file.
     * @param filename Path to read from.
     * @return Reconstructed Circuit.
     * @throws std::runtime_error if the file cannot be opened.
     */

private:
    Topology topology_;
    std::vector<std::unique_ptr<Component>> elements_;
};

#endif
