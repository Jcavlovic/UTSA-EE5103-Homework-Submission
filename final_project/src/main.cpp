#include "Circuit.h"
#include "ComponentFactory.h"
#include "Components.h"

#include <iomanip>
#include <iostream>
#include <memory>

int main() {
    std::cout << std::fixed << std::setprecision(3);

    double Vs = 0.0, R1 = 0.0, R2 = 0.0, R3 = 0.0;
    std::cout << "Enter source voltage Vs (V): ";
    std::cin >> Vs;
    std::cout << "Enter R1 (ohm): ";
    std::cin >> R1;
    std::cout << "Enter R2 (ohm): ";
    std::cin >> R2;
    std::cout << "Enter R3 (ohm): ";
    std::cin >> R3;

    Circuit series(Circuit::Topology::Series, "DC-Series");
    series.add(std::make_unique<Resistor>("R1", R1));
    series.add(std::make_unique<Resistor>("R2", R2));
    series.add(std::make_unique<Resistor>("R3", R3));

    std::cout << series << "\n";
    series.analyze(std::cout, Vs);

    Circuit parallel(Circuit::Topology::Parallel, "DC-Parallel");
    parallel.add(ComponentFactory::create("Resistor", "R4", 100.0));
    parallel.add(ComponentFactory::create("Resistor", "R5", 220.0));

    std::cout << "\n" << parallel << "\n";
    parallel.analyze(std::cout, Vs);

    Circuit combined = series + parallel;
    std::cout << "\n" << combined << "\n";
    combined.analyze(std::cout, Vs);

    Circuit twoBanks = parallel * parallel;
    std::cout << "\n" << twoBanks << "\n";
    twoBanks.analyze(std::cout, Vs);

    series.save("circuit.txt");
    Circuit loaded = Circuit::load("circuit.txt");
    std::cout << "\nReloaded from file: " << loaded << "\n";
    loaded.analyze(std::cout, Vs);

    return 0;
}
