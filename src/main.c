#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/calculator.h"

#define MAX_SIZE 1000

void printHeader() {
    printf("\n=========================================\n");
    printf("  Financial & Engineering Evaluator 🚀   \n");
    printf("=========================================\n");
    printf(" Commands:\n");
    printf("   [expr] - Type any math expression (e.g., 5*sin(1))\n");
    printf("   intg   - Enter Calculus Mode (Numerical Integration)\n");
    printf("   exit   - Quit the program\n");
    printf("-----------------------------------------\n");
}

int main() {
    char expression[MAX_SIZE];
    printHeader();
    
    while (1) {
        printf("\n>> ");
        if (fgets(expression, MAX_SIZE, stdin) == NULL) break;
        expression[strcspn(expression, "\n")] = 0; // 移除換行符號
        
        if (strcmp(expression, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        if (strlen(expression) == 0) continue;

        // 💡 進入微積分模式
        if (strcmp(expression, "intg") == 0) {
            char func_expr[MAX_SIZE];
            double a, b;
            
            printf("\n[Calculus Mode] Numerical Integration\n");
            printf("  Enter f(x) (e.g., x^2 + 2*x): ");
            if (fgets(func_expr, MAX_SIZE, stdin) == NULL) break;
            func_expr[strcspn(func_expr, "\n")] = 0;

            printf("  Lower bound (a): ");
            scanf("%lf", &a);
            printf("  Upper bound (b): ");
            scanf("%lf", &b);
            
            // 清理輸入緩衝區，避免下一次 fgets 讀到換行
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            // 執行積分，切 1000 份來逼近
            double integral_result = integrate(func_expr, a, b, 1000);
            printf("  => Integral Result: %.4f\n", integral_result);
            continue;
        }

        // 一般計算模式
        double result = evaluate(expression);
        printf("=> Result: %.4f\n", result); 
    }
    return 0;
}