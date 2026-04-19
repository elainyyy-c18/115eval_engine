#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/calculator.h" // 引用你自己寫的 library

#define MAX_SIZE 1000

int main() {
    char expression[MAX_SIZE];
    printf("=========================================\n");
    printf("  Financial Expression Evaluator (v1.0)  \n");
    printf("=========================================\n");
    
    while (1) {
        printf(">> ");
        if (fgets(expression, MAX_SIZE, stdin) == NULL) break;
        expression[strcspn(expression, "\n")] = 0;
        
        if (strcmp(expression, "exit") == 0) break;
        if (strlen(expression) == 0) continue;

        // 直接呼叫你封裝好的 API
        double result = evaluate(expression);
        printf("Result: %.2f\n\n", result); 
    }
    return 0;
}