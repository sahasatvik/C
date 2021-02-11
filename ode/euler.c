#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define STEPS   10000

double cos_(double, double);
double sin_(double, double);
double square(double, double);
double euler(double (*f)(double, double), double, double, double, int);

double cos_(double t, double y) {
        return cos(t);
}
double sin_(double t, double y) {
        return sin(t);
}
double square(double t, double y) {
        return t * t;
}

/* Implementation of Euler's method for solving first order ordinary differential equations,
 * of the form y' = f(t, y). */

double euler(double (*f)(double, double), double t0, double tn, double y0, int steps) {
        double h = (tn - t0) / steps;
        for (int i = 0; i < steps; i++) {
                /* printf("%.2f\t %.4f\n", t0, y0); */
                y0 += f(t0, y0) * h;
                t0 += h;
        }
        return y0;
}

int main(int argc, const char *argv[]) {
        double y = euler(cos_, 0, M_PI / 2, 0, STEPS);
        printf("%.2f\t %.8f\n", M_PI / 2, y);
        y = euler(sin_, 0, M_PI / 2, -1, STEPS);
        printf("%.2f\t %.8f\n", M_PI / 2, y);
        y = euler(square, 0, 10, 0, STEPS);
        printf("%.2f\t %.8f\n", 10.0, y);
        return 0;
}
