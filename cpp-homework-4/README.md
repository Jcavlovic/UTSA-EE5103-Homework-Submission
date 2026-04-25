# UTSA-EE5103-Homework-Submission
### EE-5103 Engineering Programming | Assignment 4
#### Student: Jordan Cavlovic (wpx425)

### Problem 1
##### Description
 Implements a SimpleString class that manages a dynamically allocated
 character array and behaves like a value type. Because the class owns
 raw memory through a char*, the synthesized copy-control members are
 insufficient (they would alias the same buffer). This implementation
 supplies a copy constructor, copy-assignment operator (using the
 copy-and-swap idiom for strong exception safety), and a destructor
 that together guarantee deep-copy semantics. Operators <<, ==, !=,
 and both const and non-const subscript operators are also overloaded.

##### How to Run
```
git https://github.com/Jcavlovic/UTSA-EE5103-Homework-Submission.git
cd UTSA-EE5103-Homework-Submission/cpp-homework-4
g++ /src/problem1.cpp -o problem1
./problem1
```

##### Output
![Problem 1](./data/problem1.png)

 ### Problem 2
##### Description
 Implements NumberList, a dynamically sized container of integers that
 focuses on operator semantics rather than user-defined conversions or
 callable objects. NumberList manages its own heap-allocated int array
 with explicit copy-control members (copy constructor, copy-assignment,
 destructor)

##### How to Run
```
git https://github.com/Jcavlovic/UTSA-EE5103-Homework-Submission.git
cd UTSA-EE5103-Homework-Submission/cpp-homework-4
g++ /src/problem2.cpp -o problem2
./problem2
```

##### Output
![Problem 2](./data/problem2.png)