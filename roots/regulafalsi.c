#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXITER 100

double regulafalsi(double (*f)(double), double, double, double);
double f(double);

/* Finding roots in a given interval using the method of false position */
double regulafalsi(double (*f)(double), double lo, double hi, double epsilon) {
        if (f(lo) * f(hi) > 0) {
                return lo - 1;
        }
        double x;
        double fx;
        for (int i = 0; i < MAXITER; i++) {
                x = hi - f(hi) * (hi - lo) / (f(hi) - f(lo));
                fx = f(x);
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx);
                if (fabs(fx) < epsilon) {
                        return x;
                } else if (f(lo) * f(x) < 0) {
                        hi = x;
                } else {
                        lo = x;
                }
        }
        return x;
}

double f(double x) {
        return x * x - 2.0;
}

int main(int argc, const char *argv[])
{
        double root = regulafalsi(f, 1, 2, 1e-9);
        printf("Root at %.8f\n", root);
        return 0;
}
