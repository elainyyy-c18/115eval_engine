#ifndef CALCULATOR_H
#define CALCULATOR_H

// 基本計算 (沒有變數 x)
double evaluate(const char* expression);

// 支援變數 x 的計算 (微積分引擎的核心)
double evaluate_with_x(const char* expression, double x_val);

// 數值積分演算法 (使用梯形公式)
double integrate(const char* expression, double a, double b, int steps);

#endif