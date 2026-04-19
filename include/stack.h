#ifndef STACK_H
#define STACK_H

void pushOp(char op);
char popOp();
char peekOp();
int isOpEmpty();

void pushVal(double val);
double popVal();
int isValEmpty();

#endif