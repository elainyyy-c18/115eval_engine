#ifndef STACK_H
#define STACK_H

// 宣告運算子 Stack 相關函式
void pushOp(char op);
char popOp();
char peekOp();
int isOpEmpty();

// 宣告數值 Stack 相關函式
void pushVal(double val);
double popVal();
int isValEmpty();

#endif