#include "Circuit.h"
#include "ComponentFactory.h"
#include "Components.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>

int main() {
    std::cout << std::fixed << std::setprecision(3);

    double Vs = 0.0, f = 0.0;
    double R1 = 0.0, R2 = 0.0, R3 = 0.0, C1 = 0.0, L1 = 0.0;
    std::cout << "Enter source voltage Vs (V, RMS): ";
    std::cin >> Vs;
    std::cout << "Enter source frequency f (Hz, 0 for DC): ";
    std::cin >> f;
    std::cout << "Enter R1 (ohm): ";
    std::cin >> R1;
    std::cout << "Enter R2 (ohm): ";
    std::cin >> R2;
    std::cout << "Enter R3 (ohm): ";
    std::cin >> R3;
    std::cout << "Enter C1 (F): ";
    std::cin >> C1;
    std::cout << "Enter L1 (H): ";
    std::cin >> L1;

    const double omega = 2.0 * std::acos(-1.0) * f;

    Circuit series(Circuit::Topology::Series, "AC-Series");
    series.add(std::make_unique<Resistor>("R1", R1));
    series.add(std::make_unique<Resistor>("R2", R2));
    series.add(std::make_unique<Resistor>("R3", R3));
    series.add(std::make_unique<Capacitor>("C1", C1));
    series.add(std::make_unique<Inductor>("L1", L1));

    std::cout << series << "\n";
    series.analyze(std::cout, Vs, omega);

    Circuit parallel(Circuit::Topology::Parallel, "AC-Parallel");
    parallel.add(ComponentFactory::create("Resistor", "R1", R1));
    parallel.add(ComponentFactory::create("Resistor", "R2", R2));
    parallel.add(ComponentFactory::create("Resistor", "R3", R3));
    parallel.add(ComponentFactory::create("Capacitor", "C1", C1));
    parallel.add(ComponentFactory::create("Inductor", "L1", L1));

    std::cout << "\n" << parallel << "\n";
    parallel.analyze(std::cout, Vs, omega);

    series.save("circuit.txt");
    Circuit loaded = Circuit::load("circuit_load.txt");
    std::cout << "\nReloaded from file: " << loaded << "\n";
    loaded.analyze(std::cout, Vs, omega);

    return 0;
}
