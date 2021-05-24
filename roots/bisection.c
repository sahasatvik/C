#include <stdlib.h>
#include <stdio.h>

double bisection(double (*f)(double), double, double, double);
double f(double);

/* Finding roots in a given interval using the method of successive bisection */
double bisection(double (*f)(double), double lo, double hi, double delta) {
        if (f(lo) * f(hi) > 0) {
                return lo - 1;
        }
        double x;
        double fx;
        for (int i = 0; (hi - lo) > delta; i++) {
                x = (lo + hi) / 2;
                fx = f(x);
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx);
                if (f(lo) * fx <= 0) {
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
        double root = bisection(f, 1, 2, 1e-9);
        printf("Root at %.8f\n", root);
        return 0;
}
