# EE 5103 / EE 4953 — Final Programming Project
### Circuit Analysis Library in C++
**Student:** Jordan Cavlovic

## Overview
A small library for building and analyzing simple AC circuits. The user can
construct resistors, capacitors, inductors, and voltage sources, combine
them in series or parallel circuits, compute the equivalent complex
impedance at any angular frequency, and save/load circuits as text files.

Series and parallel circuits can also be combined with the overloaded `+`
and `*` operators.

## Build and run
From the `final_project/` directory:
```
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o circuit_app
./circuit_app
```

## Files
- `Component.{h,cpp}` — abstract base class
- `Components.{h,cpp}` — Resistor, Capacitor, Inductor, VoltageSource
- `Circuit.{h,cpp}` — series/parallel container with operator overloading and file I/O
- `ComponentFactory.{h,cpp}` — builds a leaf component from its type name
- `main.cpp` — demo program
