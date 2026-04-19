# Financial Expression Evaluator 🧮

A highly precise, C-based command-line expression evaluator designed to handle complex financial calculations. 

## 💡 Motivation
Traditional basic calculators often fail to handle complex operational precedence or lack the precision required for accounting and financial models. This project integrates the **Shunting-yard algorithm** learned in Data Structures to parse complex mathematical expressions directly from string inputs, ensuring both $O(n)$ time complexity efficiency and high precision.

## 🚀 Features
* **Modular Architecture**: Clean separation of Data Structures (`stack.h/c`) and Algorithms (`calculator.h/c`).
* **Algorithmic Efficiency**: Utilizes Dijkstra's Shunting-yard algorithm for Infix to Postfix conversion.
* **Financial Precision**: Implemented using `double` precision floating-point arithmetic to accurately manage decimals in financial contexts.
* **Robust Error Handling**: Safely handles division by zero, mismatched parentheses, and unary minus operations.

## 🛠️ Tech Stack
* Language: Standard C
* Core DSA: Stacks, String Parsing, Shunting-yard Algorithm

## 💻 How to Compile and Run
Navigate to the project root directory and compile using `gcc`:
```bash
gcc src/main.c src/stack.c src/calculator.c -I include -o financial_calc -lm
./financial_calc