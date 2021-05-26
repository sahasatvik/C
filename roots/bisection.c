#include <stdlib.h>
#include <stdio.h>

double bisection(double (*f)(double), double, double, double);
double f(double);

/* Finding roots in a given interval using the method of successive bisection */
double bisection(double (*f)(double), double lo, double hi, double delta) {
        double x;
        double fx, flo = f(lo), fhi = f(hi);
        if (flo == 0.0) {
                return lo;
        } else if (fhi == 0.0) {
                return hi;
        } else if (flo * fhi > 0) {
                return lo - 1;
        }
        for (int i = 0; (hi - lo) > delta; i++) {
                x = (lo + hi) / 2;
                fx = f(x);
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx);
                if (fx == 0.0) {
                        break;
                } else if (flo * fx < 0) {
                        hi = x;
                        fhi = fx;
                } else {
                        lo = x;
                        flo = fx;
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
