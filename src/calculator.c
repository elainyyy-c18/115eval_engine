#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../include/calculator.h"
#include "../include/stack.h"

double evaluate_vars(const char* expression, double x_val, double y_val, double z_val) {
    int len = strlen(expression);
    for (int i = 0; i < len; i++) {
        if (isspace(expression[i])) continue;

        // 1. 處理數字
        if (isdigit(expression[i]) || expression[i] == '.') {
            char buffer[32];
            int k = 0;
            while (i < len && (isdigit(expression[i]) || expression[i] == '.')) buffer[k++] = expression[i++];
            buffer[k] = '\0';
            pushVal(atof(buffer));
            i--; 
        }
        // 2. 處理變數與函數
        else if (isalpha(expression[i])) {
            char func[16];
            int k = 0;
            while (i < len && isalpha(expression[i])) func[k++] = expression[i++];
            func[k] = '\0';
            
            // 攔截多變數
            if (strcmp(func, "x") == 0) { pushVal(x_val); i--; continue; }
            if (strcmp(func, "y") == 0) { pushVal(y_val); i--; continue; }
            if (strcmp(func, "z") == 0) { pushVal(z_val); i--; continue; }
            
            // 略過函數名稱與括號之間的空格
            int temp_i = i;
            while (temp_i < len && isspace(expression[temp_i])) temp_i++;
            
            if (expression[temp_i] == '(') {
                i = temp_i; // 將 i 移動到 '(' 的位置
                int count = 1; char inner[128]; int j = 0; i++; 
                while (i < len && count > 0) {
                    if (expression[i] == '(') count++;
                    if (expression[i] == ')') count--;
                    if (count > 0) inner[j++] = expression[i++];
                }
                inner[j] = '\0';
                
                double inner_val = evaluate_vars(inner, x_val, y_val, z_val); 

                if (strcmp(func, "sin") == 0) pushVal(sin(inner_val));
                else if (strcmp(func, "cos") == 0) pushVal(cos(inner_val));
                else if (strcmp(func, "sqrt") == 0) pushVal(sqrt(inner_val));
                else if (strcmp(func, "log") == 0) pushVal(log(inner_val));
                else { printf("\n[Error] Unknown function: '%s'\n", func); exit(1); }
            } else {
                // 💡 抓蟲：如果沒有括號，阻止程式靜默崩潰！
                printf("\n[Syntax Error] Missing '(' after '%s'. Did you mean %s(...) or forget a '*' (e.g. 2*x)?\n", func, func);
                exit(1);
            }
        }
        else if (expression[i] == '(') pushOp('(');
        else if (expression[i] == ')') {
            while (!isOpEmpty() && peekOp() != '(') applyOp();
            popOp(); 
        }
        // 3. 處理運算子
        else {
            // 💡 抓蟲：工業級的「負號 (Unary Minus)」探測器
            if (expression[i] == '-') {
                int is_unary = 1; // 預設為負號
                // 往回找前一個非空白字元
                for (int j = i - 1; j >= 0; j--) {
                    if (!isspace(expression[j])) {
                        // 如果前一個字元是數字、右括號、或變數(英文字母)，那就是「減法」
                        if (isdigit(expression[j]) || expression[j] == ')' || isalpha(expression[j]) || expression[j] == '.') {
                            is_unary = 0; 
                        }
                        break;
                    }
                }
                // 如果判定是負號，我們推入 0.0，讓程式執行 0.0 - x
                if (is_unary) pushVal(0.0);
            }

            while (!isOpEmpty() && precedence(peekOp()) >= precedence(expression[i])) applyOp();
            pushOp(expression[i]);
        }
    }
    while (!isOpEmpty()) applyOp();
    return popVal();
}

double evaluate(const char* expression) {
    return evaluate_vars(expression, 0, 0, 0);
}

// ---------------------------------------------------------
// 🔥 高階微積分引擎 (Advanced Calculus Engine)
// ---------------------------------------------------------

// 1. 數值微分 (Central Difference Method)
double derive(const char* expression, double x_val) {
    double h = 1e-5; // 極小值
    return (evaluate_vars(expression, x_val + h, 0, 0) - evaluate_vars(expression, x_val - h, 0, 0)) / (2 * h);
}

// 2. 單變數積分 (一重)
double integrate_1d(const char* expression, double a, double b, int steps) {
    double h = (b - a) / steps;
    double sum = 0.5 * (evaluate_vars(expression, a, 0, 0) + evaluate_vars(expression, b, 0, 0));
    for (int i = 1; i < steps; i++) {
        sum += evaluate_vars(expression, a + i * h, 0, 0);
    }
    return sum * h;
}

// 3. 雙變數積分 (二重：Midpoint Rule)
double integrate_2d(const char* expression, double ax, double bx, double ay, double by, int steps) {
    double hx = (bx - ax) / steps;
    double hy = (by - ay) / steps;
    double sum = 0;
    for (int i = 0; i < steps; i++) {
        double x = ax + (i + 0.5) * hx;
        for (int j = 0; j < steps; j++) {
            double y = ay + (j + 0.5) * hy;
            sum += evaluate_vars(expression, x, y, 0);
        }
    }
    return sum * hx * hy;
}

// 4. 三變數積分 (三重：Midpoint Rule)
double integrate_3d(const char* expression, double ax, double bx, double ay, double by, double az, double bz, int steps) {
    double hx = (bx - ax) / steps;
    double hy = (by - ay) / steps;
    double hz = (bz - az) / steps;
    double sum = 0;
    // 為了效能，3D 積分的 steps 不建議設太大 (例如 50^3 = 125,000 次計算)
    for (int i = 0; i < steps; i++) {
        double x = ax + (i + 0.5) * hx;
        for (int j = 0; j < steps; j++) {
            double y = ay + (j + 0.5) * hy;
            for (int k = 0; k < steps; k++) {
                double z = az + (k + 0.5) * hz;
                sum += evaluate_vars(expression, x, y, z);
            }
        }
    }
    return sum * hx * hy * hz;
}