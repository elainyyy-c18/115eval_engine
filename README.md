# 🧮 Multivariable Calculus Engine with Python GUI

![Backend](https://img.shields.io/badge/Backend-Standard_C-blue.svg)
![Frontend](https://img.shields.io/badge/Frontend-Python_Tkinter-yellow.svg)
![Data Structures](https://img.shields.io/badge/Core-Data_Structures-green.svg)
![Calculus](https://img.shields.io/badge/Math-Multivariable_Calculus-orange.svg)

A modern, high-performance numerical analysis software implementing a **Frontend-Backend Architecture**. This project bridges the precision required in financial accounting with advanced algorithmic parsing and multivariable calculus computation, built entirely from scratch.

## 💡 Motivation
This project was born from the desire to integrate cross-disciplinary knowledge. Standard calculators lack the flexibility to handle complex multivariable integration, while professional math software is often too bloated. 

By combining the **Shunting-yard algorithm** (learned in Data Structures) with numerical methods (learned in Advanced Calculus), this system utilizes Standard C for rigorous, memory-efficient computations, and Python for a user-friendly Graphical User Interface (GUI), demonstrating cross-language system integration.

## 🚀 Core Features

### 1. The Backend: Advanced Parsing & Calculus Engine (C)
* **O(n) Time Complexity:** Implements Dijkstra's Shunting-yard algorithm to convert infix expressions to postfix notation via dynamic Stack structures.
* **Lexical Analysis:** Custom tokenizer that natively recognizes multi-character engineering functions (`sin`, `cos`, `sqrt`, `log`) and multivariable inputs (`x`, `y`, `z`).
* **Numerical Calculus:** * Implements the Central Difference Method to approximate $f'(x)$ with high precision.
  * Natively supports 1D, 2D, and 3D definite integrals (e.g., calculating areas and volumes) using the Midpoint Riemann Sum method through nested algorithmic loops.

### 2. The Frontend: Interactive GUI (Python)
* **Cross-Platform UI:** Uses `Tkinter` to provide a tabbed interface for different calculus modes.
* **Inter-Process Communication (IPC):** Dynamically passes user parameters to the C backend via standard I/O (`subprocess`), enabling headless execution and seamless data retrieval.

## 📂 Project Architecture
The project strictly adheres to modular programming principles:
```text
115eval_engine/
├── include/           # C Header files defining APIs (`stack.h`, `calculator.h`)
├── src/               # C Source code (`stack.c`, `calculator.c`, `main.c`)
├── Makefile           # Automated build configuration
├── financial_calc.exe # Compiled C Execution Engine (Backend)
└── gui.py             # Python Tkinter Application (Frontend)
```

## 💻 Installation & Usage

**Step 1: Compile the C Backend Engine**
Ensure you have `gcc` installed, then build the engine using the provided Makefile:
```bash
git clone https://github.com/elainyyy-c18/115eval_engine.git
cd 115eval_engine
make
```

**Step 2: Launch the GUI Frontend**
Requires Python 3.x. No external dependencies (`pip`) are needed!
```bash
python gui.py
```

## 🎮 Execution Modes

The software supports two ways of interaction:

### Method A: Graphical User Interface (GUI)
Simply launch `gui.py` and navigate through the interactive tabs:
* **Basic Math:** Evaluates complex precedence and functions (e.g., `5 * (sin(x) + cos(x))`).
* **Derivatives:** Calculates $f'(x)$ at any given point.
* **Multiple Integrals:** Dedicated UI grids for inputting bounds $(a, b)$ for variables $x$, $y$, and $z$.

### Method B: Command Line Interface (CLI) / Headless Mode
For direct terminal access, run `./financial_calc`.

**Example: Computing a Double Integral (`int2`) via CLI**
```text
>> int2
  [2D Double Integral] Enter f(x,y): x*y
  x bounds (a b): 0 2
  y bounds (c d): 0 3
  => Result: 9.000000
```