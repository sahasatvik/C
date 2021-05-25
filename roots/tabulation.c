#include <stdlib.h>
#include <stdio.h>

void tabulation(double (*f)(double), double, double, int);
double f(double);

/* Finding intervals containing roots using tabulation */
void tabulation(double (*f)(double), double lo, double hi, int n) {
        double h = (hi - lo) / n;
        double x = lo;
        double fx1 = f(lo);
        double fx2;
        printf("Step %3d : x = %.8f, f(x) = %+.8f\n", 0, x, fx1);
        for (int i = 1; i <= n; i++) {
                fx2 = f(x + h);
                if (fx1 * fx2 <= 0) {
                        printf("\tRoot between x = %.8f and  %.8f\n", x, x + h);
                }
                fx1 = fx2;
                x = x + h;
                printf("Step %3d : x = %.8f, f(x) = %+.8f\n", i, x, fx1);
        }
}

double f(double x) {
        return x * x - 2.0;
}

int main(int argc, const char *argv[])
{
        tabulation(f, 1, 2, 20);
        return 0;
}
