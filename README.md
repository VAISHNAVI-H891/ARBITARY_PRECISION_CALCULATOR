# Arbitrary Precision Calculator (APC) – C

A high-performance **Arbitrary Precision Calculator** built in C that performs arithmetic operations on extremely large numbers beyond the limits of standard data types. The project uses a **Linked List–based Abstract Data Type (ADT)** to dynamically store and process numbers with precision limited only by system memory.

## Why This Project?

Standard data types (`int`, `long`, etc.) support limited precision (typically 32–64 bits). This calculator enables:

* Computation on numbers with **hundreds or thousands of digits**
* Memory-efficient storage using dynamic data structures
* Real-world exposure to **data structures + system-level programming**
  
## Features

* Supports very large integers and decimal numbers
* Operations implemented:

  * Addition (`+`)
  * Subtraction (`-`)
  * Multiplication (`*`)
  * Division (`/`)
  * Modulus (`%`)
  * Power (`^`)
* Operator detection from a single input expression
* Linked list storage sliced based on `sizeof(int)` (portable design)
* Efficient carry/borrow handling
* Optimized handling for special cases (like zero inputs)
* Clean modular code structure
* Interactive command-line interface

## How It Works

1. User enters an expression:
   number1 operator number2
   Example:
   1234567890121234518775261672673+718625634152778367635544816
2. The program:
   * Parses the operator
   * Splits the input into two numbers
   * Stores each number across multiple linked list nodes
   * Performs the selected operation
   * Generates the result as a new linked list
   * Displays the output
     
## Sample Run

$ ./apc
Enter the input:
1234567890121234518775261672673+718625634152778367635544816

Result:
1235286515755387297142897217489

Want to continue? Press [yY | nN]

## Special Case Optimization

* If `Num1 = 0` → Output `Num2`
* If `Num2 = 0` → Output `Num1`
* If both are `0` → Output `0`
* Leading zeros removed
* Reduces unnecessary computation
* 
## Data Structure Used

**Linked List (ADT)**

* Each node stores a chunk of digits
* Enables dynamic memory allocation
* Supports arbitrary precision operations efficiently

## Project Structure (Typical)
.
├── main.c
├── addition.c
├── subtraction.c
├── multiplication.c
├── division.c
├── power.c
├── list.c
├── apc.h
├── Makefile
└── README.md

## Compilation & Execution

### Compile

gcc *.c -o apc

### Run
./apc
## Applications

* Public-key cryptography (large integer arithmetic)
* Scientific and engineering computations
* High-precision mathematical calculations (π, e, etc.)
* Learning advanced data structures and memory management

## Skills Demonstrated

* Data Structures (Linked Lists)
* Dynamic Memory Management
* Modular Programming in C
* Expression Parsing
* Algorithm Design for Big Number Arithmetic
* Edge Case Handling & Optimization
* 
## Future Enhancements

* Support for negative numbers
* Multiple expression evaluation
* Floating-point precision improvements
* Performance optimization for very large inputs
* GUI version
  
## Author

**Vaishnavi**

---

## Note

This project was developed as part of a Data Structures learning initiative to explore real-world implementation of arbitrary precision arithmetic using C.
