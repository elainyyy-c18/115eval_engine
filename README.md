# 🧮 Multivariable Calculus & Financial Expression Engine

![C Standard](https://img.shields.io/badge/Language-Standard_C-blue.svg)
![Data Structures](https://img.shields.io/badge/Core-Data_Structures-green.svg)
![Calculus](https://img.shields.io/badge/Math-Multivariable_Calculus-orange.svg)

A high-performance, command-line numerical analysis engine built in Standard C. This project bridges the precision required in financial accounting with advanced algorithmic parsing and multivariable calculus computation.

## 💡 Motivation
This project was born from the desire to integrate cross-disciplinary knowledge. Standard calculators lack the flexibility to handle complex operational precedence or multivariable functions. By combining the **Shunting-yard algorithm** (from Data Structures) with numerical methods (learned in advanced calculus), this engine can perform real-time parsing of mathematical expressions and evaluate derivatives and multiple integrals dynamically without relying on external mathematical software.

## 🚀 Core Features

### 1. Advanced String Parsing & Evaluation
* **O(n) Time Complexity:** Implements Dijkstra's Shunting-yard algorithm to convert infix expressions to postfix notation via dynamic Stack structures.
* **Lexical Analysis:** Custom tokenizer that natively recognizes multi-character engineering functions (`sin`, `cos`, `sqrt`, `log`) and multivariable inputs (`x`, `y`, `z`).

### 2. Numerical Calculus Engine
* **Numerical Differentiation:** Implements the Central Difference Method to approximate $f'(x)$ with high precision.
* **Multivariable Integration:** Natively supports 1D, 2D, and 3D definite integrals (e.g., calculating areas and volumes) using the Midpoint Riemann Sum method through nested algorithmic loops.

## 📂 Project Architecture
The project strictly adheres to modular C programming principles for high maintainability:
* `include/` : Header files defining the APIs (`stack.h`, `calculator.h`).
* `src/stack.c` : Encapsulated Stack data structure implementation.
* `src/calculator.c` : The core parsing and numerical calculus engine.
* `src/main.c` : The Interactive Command Line Interface (CLI).
* `Makefile` : Automated build configuration.

## 💻 Installation & Compilation
Clone the repository and build the engine using the provided Makefile:

```bash
git clone https://github.com/your-username/Financial-Expression-Evaluator.git
cd Financial-Expression-Evaluator
make
./financial_calc
```

## 🎮 Usage Guide & Demo

The CLI provides several modes. Enter a command at the `>>` prompt:

* **Basic & Engineering Math:** Simply type the expression.
  `>> 5 * (sin(x) + cos(x))`
* **`diff` Mode (Differentiation):** Evaluates the slope of a function at a specific point.
* **`int1` Mode (1D Integral):** Evaluates $\int_a^b f(x) dx$.
* **`int2` Mode (Double Integral):** Evaluates the volume under a surface $\iint f(x,y) dx dy$.
* **`int3` Mode (Triple Integral):** Evaluates multi-dimensional integrals $\iiint f(x,y,z) dx dy dz$.

**Example: Computing a Double Integral (`int2`)**

```text
>> int2
  [2D Double Integral] Enter f(x,y): x*y
  x bounds (a b): 0 2
  y bounds (c d): 0 3
  => Result: 9.000000
```