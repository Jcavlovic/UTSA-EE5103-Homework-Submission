# EE 5103 / EE 4953 — Final Project
### Circuit Analysis Library in C++
**Student:** Jordan Cavlovic

## Overview
A small library for building and analyzing simple AC circuits. The user can
construct resistors, capacitors, inductors, and voltage sources, combine
them in series or parallel circuits, compute the equivalent resistance,
the current drawn from the source, the voltage drop across each component,
and the power dissipated, and save/load circuits as text files.

Series and parallel circuits can also be combined with the overloaded `+`
and `*` operators.

## Build and run
```
git https://github.com/Jcavlovic/UTSA-EE5103-Homework-Submission.git
cd UTSA-EE5103-Homework-Submission/final_project
g++ src/*.cpp -o circuit_app
./circuit_app
```

## Files
- `src/Component.{h,cpp}` — abstract base class
- `src/Components.{h,cpp}` — Resistor, Capacitor, Inductor, VoltageSource
- `src/Circuit.{h,cpp}` — series/parallel container with operator overloading and file I/O
- `src/ComponentFactory.{h,cpp}` — builds a leaf component from its type name
- `src/main.cpp` — demo program
