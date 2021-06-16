#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
   Testing the getopt() method of parsing command line arguments.
 */

int main(int argc, char * const argv[]) {
        int c;
        while ((c = getopt(argc, argv, ":haf:")) != -1) {
                switch (c) {
                        case 'h':
                                printf("Command line argument parser.\n");
                                exit(0);
                                break;
                        case 'a':
                                printf("Option -%c\n", optopt);
                                break;
                        case 'f':
                                printf("Argument for -%c: %s\n", optopt, optarg);
                                break;
                        case ':':
                                printf("Missing argument for option -%c\n", optopt);
                                break;
                        case '?':
                                printf("Unknown option : %c\n", optopt);
                }         
        }
        return 0;
}
