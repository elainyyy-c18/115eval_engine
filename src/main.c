#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/calculator.h"

#define MAX_SIZE 1000

void printHeader() {
    printf("\n=============================================\n");
    printf("  Multivariable Calculus & Eval Engine 🚀  \n");
    printf("=============================================\n");
    printf(" Commands:\n");
    printf("   [expr] - Calculate basic math (e.g., 5*sin(1))\n");
    printf("   diff   - Mode: Numerical Differentiation f'(x)\n");
    printf("   int1   - Mode: Definite Integral (1D)\n");
    printf("   int2   - Mode: Double Integral (2D)\n");
    printf("   int3   - Mode: Triple Integral (3D)\n");
    printf("   exit   - Quit\n");
    printf("---------------------------------------------\n");
}

int main() {
    char expression[MAX_SIZE];
    printHeader();
    
    while (1) {
        printf("\n>> ");
        if (fgets(expression, MAX_SIZE, stdin) == NULL) break;
        expression[strcspn(expression, "\n")] = 0; 
        
        if (strcmp(expression, "exit") == 0) break;
        if (strlen(expression) == 0) continue;

        if (strcmp(expression, "diff") == 0) {
            char func[MAX_SIZE]; double x_val;
            printf("  [Derivative] Enter f(x): ");
            scanf("%s", func);
            printf("  Evaluate at x = ");
            scanf("%lf", &x_val);
            while(getchar() != '\n'); 
            printf("  => f'(%.2f) approx: %.6f\n", x_val, derive(func, x_val));
            continue;
        }

        if (strcmp(expression, "int1") == 0) {
            char func[MAX_SIZE]; double a, b;
            printf("  [1D Integral] Enter f(x): "); scanf("%s", func);
            printf("  Lower (a) & Upper (b): "); scanf("%lf %lf", &a, &b);
            while(getchar() != '\n');
            printf("  => Result: %.6f\n", integrate_1d(func, a, b, 1000));
            continue;
        }

        if (strcmp(expression, "int2") == 0) {
            char func[MAX_SIZE]; double ax, bx, ay, by;
            printf("  [2D Double Integral] Enter f(x,y): "); scanf("%s", func);
            printf("  x bounds (a b): "); scanf("%lf %lf", &ax, &bx);
            printf("  y bounds (c d): "); scanf("%lf %lf", &ay, &by);
            while(getchar() != '\n');
            printf("  => Result: %.6f\n", integrate_2d(func, ax, bx, ay, by, 200));
            continue;
        }

        if (strcmp(expression, "int3") == 0) {
            char func[MAX_SIZE]; double ax, bx, ay, by, az, bz;
            printf("  [3D Triple Integral] Enter f(x,y,z): "); scanf("%s", func);
            printf("  x bounds (a b): "); scanf("%lf %lf", &ax, &bx);
            printf("  y bounds (c d): "); scanf("%lf %lf", &ay, &by);
            printf("  z bounds (e f): "); scanf("%lf %lf", &az, &bz);
            while(getchar() != '\n');
            // 注意：3D 迴圈次數(50)代表 50*50*50 = 125,000次計算，以防 C 語言跑太久
            printf("  => Result: %.6f\n", integrate_3d(func, ax, bx, ay, by, az, bz, 50));
            continue;
        }

        double result = evaluate(expression);
        printf("=> Result: %.6f\n", result); 
    }
    return 0;
}