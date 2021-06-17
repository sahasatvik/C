#include <stdio.h>
#include <math.h>

unsigned long long strtollu(const char *);
unsigned long long iscube(unsigned long long);

/*
   Displays all the ways the number supplied as a command line argument can
   be expressed as the sum of two cubes.
 */

int main(int argc, const char *argv[]) {
        unsigned long long number = 0;
        if (argc > 1)
                number = strtollu(argv[1]);
        for (unsigned long long i = 1; i < number; i++) {
                unsigned long long cube, root;
                cube = i * i * i;
                if (cube > number / 2)
                        break;
                root = iscube(number - cube);
                if (root)
                        printf("%llu \t%llu\n", i, root);
        }
        return 0;
}

unsigned long long strtollu(const char *arg) {
        unsigned long long n = 0;
        while (*arg != '\0')
                n = n * 10 + (*arg++ - '0');
        return n;
}

unsigned long long iscube(unsigned long long n) {
        unsigned long long root = round(cbrt(n));
        if (n == root * root * root)
                return root;
        return 0;
}
