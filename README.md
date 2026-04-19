# Financial & Engineering Expression Evaluator 🧮

A robust, highly precise C-based command-line expression evaluator. It is designed to handle complex financial calculations, engineering mathematical functions, and even numerical calculus.

## 💡 Motivation
This project bridges the gap between accounting precision requirements and advanced algorithmic logic. By integrating the **Shunting-yard algorithm** learned in Data Structures and mathematical concepts from Calculus, this tool not only parses strings into executable math but also performs real-time numerical integration. 

## 🚀 Features
* **Modular Architecture:** Clean separation of Data Structures (`stack.h/c`) and Algorithms (`calculator.h/c`).
* **Algorithmic Efficiency:** Utilizes Dijkstra's Shunting-yard algorithm for Infix to Postfix conversion with $O(n)$ time complexity.
* **Engineering Functions:** Custom lexer/tokenizer to support advanced trigonometric and logarithmic functions (`sin`, `cos`, `sqrt`, `log`).
* **Calculus Engine:** Implements the Trapezoidal Rule for numerical definite integration ($\int_a^b f(x) dx$), parsing algebraic expressions containing the variable `x`.

## 🛠️ Tech Stack
* Language: Standard C
* Core concepts: Stacks, String Parsing, Numerical Methods (Trapezoidal Rule)

## 💻 How to Compile and Run
Ensure you have `gcc` installed, then build the project using the provided Makefile:
```bash
make
./financial_calc