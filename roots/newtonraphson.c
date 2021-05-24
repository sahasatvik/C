#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXITER 100

double newtonraphson(double (*f)(double), double (*df)(double), double, double);
double f(double);
double df(double);

/* Finding roots in a given interval using the Newton-Raphson method */
double newtonraphson(double (*f)(double), double (*df)(double), double x, double epsilon) {
        double fx;
        for (int i = 0; i < MAXITER; i++) {
                fx = f(x);
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx);
                if (fabs(fx) < epsilon) {
                        return x;
                }
                x -= f(x) / df(x);
        }
        return x;
}

double f(double x) {
        return x * x - 2.0;
}
double df(double x) {
        return 2 * x;
}

int main(int argc, const char *argv[])
{
        double root = newtonraphson(f, df, 1, 1e-9);
        printf("Root at %.8f\n", root);
        return 0;
}
