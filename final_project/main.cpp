#include "Circuit.h"
#include "ComponentFactory.h"
#include "Components.h"

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <memory>

int main() {
    constexpr double pi = 3.14159265358979;
    const double freq = 60.0;
    const double omega = 2.0 * pi * freq;

    std::cout << std::fixed << std::setprecision(3);

    double R = 0.0, L = 0.0, C = 0.0;
    std::cout << "Enter resistance R (ohm): ";
    std::cin >> R;
    std::cout << "Enter inductance L (H): ";
    std::cin >> L;
    std::cout << "Enter capacitance C (F): ";
    std::cin >> C;

    Circuit series(Circuit::Topology::Series, "RLC Series");
    series.add(std::make_unique<Resistor>("R1", R));
    series.add(std::make_unique<Inductor>("L1", L));
    series.add(std::make_unique<Capacitor>("C1", C));

    std::cout << series << "\n";
    for (const auto& e : series.elements()) {
        std::cout << "  " << *e << "\n";
    }
    auto z = series.impedance(omega);
    std::cout << "Impedance at 60 Hz: " << z.real() << " + j" << z.imag()
              << " ohm   Impedence = " << std::abs(z) << " ohm\n";

    // Parallel RC built via the factory.
    Circuit parallel(Circuit::Topology::Parallel, "RC Parallel");
    parallel.add(ComponentFactory::create("Resistor",  "R2", 1000.0));
    parallel.add(ComponentFactory::create("Capacitor", "C2", 4.7e-6));

    std::cout << "\n" << parallel << "\n";
    z = parallel.impedance(omega);
    std::cout << "Impedance at 60 Hz: " << z.real() << " + j" << z.imag()
              << " ohm   Impedence = " << std::abs(z) << " ohm\n";

    Circuit combined = series + parallel;
    std::cout << "\n" << combined << "\n";
    std::cout << "  Impedence at 60 Hz: "
              << std::abs(combined.impedance(omega)) << " ohm\n";

    Circuit twoBanks = parallel * parallel;
    std::cout << twoBanks << "\n";
    std::cout << "  Impedence at 60 Hz: "
              << std::abs(twoBanks.impedance(omega)) << " ohm\n";

    series.save("circuit.txt");
    Circuit loaded = Circuit::load("circuit.txt");
    std::cout << "\nReloaded from file: " << loaded << "\n";
    std::cout << "  Impedence at 60 Hz: "
              << std::abs(loaded.impedance(omega)) << " ohm\n";

    return 0;
}
