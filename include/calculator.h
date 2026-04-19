#ifndef CALCULATOR_H
#define CALCULATOR_H

double evaluate(const char* expression);
double evaluate_vars(const char* expression, double x_val, double y_val, double z_val);

double derive(const char* expression, double x_val);
double integrate_1d(const char* expression, double a, double b, int steps);
double integrate_2d(const char* expression, double ax, double bx, double ay, double by, int steps);
double integrate_3d(const char* expression, double ax, double bx, double ay, double by, double az, double bz, int steps);

#endif