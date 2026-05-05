# EE 5103 / EE 4953 — Final Programming Project
### Circuit Analysis Library in C++
**Student:** Jordan Cavlovic

## Overview
A small library for building and analyzing simple DC circuits. The user can
construct resistors, capacitors, inductors, and voltage sources, combine
them in series or parallel circuits, compute the equivalent resistance,
the current drawn from the source, the voltage drop across each component,
and the power dissipated, and save/load circuits as text files.

Series and parallel circuits can also be combined with the overloaded `+`
and `*` operators.

## Build and run
From the `final_project/` directory:
```
g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o circuit_app
./circuit_app
```

## Files
- `src/Component.{h,cpp}` — abstract base class
- `src/Components.{h,cpp}` — Resistor, Capacitor, Inductor, VoltageSource
- `src/Circuit.{h,cpp}` — series/parallel container with operator overloading and file I/O
- `src/ComponentFactory.{h,cpp}` — builds a leaf component from its type name
- `src/main.cpp` — demo program
