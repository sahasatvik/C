#include <stdlib.h>
#include <stdio.h>

char *months[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
};

/*
   Display the names of the months whose numbers (from 1 to 12) are supplied
   as command line arguments.
 */

int main(int argc, const char *argv[]) {
        for (int i = 1; i < argc; i++) {
                int n = atoi(argv[i]);
                if (n >= 1 && n <= 12)
                        printf("%s\n", months[n - 1]);
        }
        return 0;
}
