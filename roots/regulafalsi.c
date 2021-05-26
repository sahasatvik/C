#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXITER 100

double regulafalsi(double (*f)(double), double, double, double);
double f(double);

/* Finding roots in a given interval using the method of false position */
double regulafalsi(double (*f)(double), double lo, double hi, double epsilon) {
        double x;
        double fx, flo = f(lo), fhi = f(hi);
        if (flo * fhi > 0) {
                return lo - 1;
        }
        for (int i = 0; i < MAXITER; i++) {
                x = hi - fhi * (hi - lo) / (fhi - flo);
                fx = f(x);
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx);
                if (fabs(fx) < epsilon) {
                        return x;
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
        double root = regulafalsi(f, 1, 2, 1e-9);
        printf("Root at %.8f\n", root);
        return 0;
}
