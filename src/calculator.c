#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/calculator.h"
#include "../include/stack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void applyOp() {
    double b = popVal();
    double a = popVal();
    char op = popOp();
    double result = 0;

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) { printf("Error: Div by 0\n"); exit(1); }
            result = a / b; break;
        case '^': result = pow(a, b); break;
    }
    pushVal(result);
}

// 核心計算引擎 (加入了變數 x_val 的支援)
double evaluate_with_x(const char* expression, double x_val) {
    int len = strlen(expression);
    for (int i = 0; i < len; i++) {
        if (isspace(expression[i])) continue;

        if (isdigit(expression[i]) || expression[i] == '.') {
            char buffer[32];
            int k = 0;
            while (i < len && (isdigit(expression[i]) || expression[i] == '.')) {
                buffer[k++] = expression[i++];
            }
            buffer[k] = '\0';
            pushVal(atof(buffer));
            i--; 
        }
        else if (isalpha(expression[i])) {
            char func[16];
            int k = 0;
            while (i < len && isalpha(expression[i])) {
                func[k++] = expression[i++];
            }
            func[k] = '\0';
            
            // 💡 新增：攔截變數 'x'
            if (strcmp(func, "x") == 0) {
                pushVal(x_val);
                i--; // 因為外層迴圈會 i++，這裡先退一步
                continue;
            }
            
            if (expression[i] == '(') {
                int count = 1;
                char inner[128];
                int j = 0;
                i++; 
                while (i < len && count > 0) {
                    if (expression[i] == '(') count++;
                    if (expression[i] == ')') count--;
                    if (count > 0) inner[j++] = expression[i++];
                }
                inner[j] = '\0';
                
                // 函數內部的計算也必須繼承 x_val
                double inner_val = evaluate_with_x(inner, x_val); 

                if (strcmp(func, "sin") == 0) pushVal(sin(inner_val));
                else if (strcmp(func, "cos") == 0) pushVal(cos(inner_val));
                else if (strcmp(func, "sqrt") == 0) pushVal(sqrt(inner_val));
                else if (strcmp(func, "log") == 0) pushVal(log(inner_val));
                else printf("Unknown func: %s\n", func);
            }
        }
        else if (expression[i] == '(') {
            pushOp('(');
        }
        else if (expression[i] == ')') {
            while (!isOpEmpty() && peekOp() != '(') applyOp();
            popOp(); 
        }
        else {
            while (!isOpEmpty() && precedence(peekOp()) >= precedence(expression[i])) {
                applyOp();
            }
            pushOp(expression[i]);
        }
    }

    while (!isOpEmpty()) applyOp();
    return popVal();
}

// 為了相容原本的標準計算
double evaluate(const char* expression) {
    return evaluate_with_x(expression, 0.0);
}

// 💡 終極武器：梯形公式數值積分 (Trapezoidal Rule)
double integrate(const char* expression, double a, double b, int steps) {
    double h = (b - a) / steps;
    // f(a) + f(b) 的一半
    double sum = 0.5 * (evaluate_with_x(expression, a) + evaluate_with_x(expression, b));
    
    // 加上中間所有的 f(x_i)
    for (int i = 1; i < steps; i++) {
        double x = a + i * h;
        sum += evaluate_with_x(expression, x);
    }
    return sum * h;
}