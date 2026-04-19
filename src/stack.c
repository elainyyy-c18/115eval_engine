#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

#define MAX_SIZE 1000

// 運算子 Stack (char)
static char opStack[MAX_SIZE];
static int opTop = -1;

// 數值 Stack (double)
static double valStack[MAX_SIZE];
static int valTop = -1;

// --- 運算子操作 ---
void pushOp(char op) {
    if (opTop < MAX_SIZE - 1) opStack[++opTop] = op;
}

char popOp() {
    if (opTop >= 0) return opStack[opTop--];
    return '\0';
}

char peekOp() {
    if (opTop >= 0) return opStack[opTop];
    return '\0';
}

int isOpEmpty() {
    return opTop == -1;
}

// --- 數值操作 ---
void pushVal(double val) {
    if (valTop < MAX_SIZE - 1) valStack[++valTop] = val;
}

double popVal() {
    if (valTop >= 0) return valStack[valTop--];
    return 0.0;
}

int isValEmpty() {
    return valTop == -1;
}