#include <stdio.h>

#define MAXLEN 1000

int getline_(char *, int);
int strindex(const char *, const char *);

/*
   Show lines in standard input which contain the first command line argument string.
   From 'The C Programming Language' by Kernighan and Ritchie.
 */

int main(int argc, const char *argv[]) {
        char line[MAXLEN];
        if (argc <= 1)
                return 1;
        while (getline_(line, MAXLEN) > 0)
                if (strindex(argv[1], line) >= 0)
                        printf("%s", line);
        return 0;
}

/* Get a line from standard input into target */
int getline_(char *target, int maxlen) {
        int i, c;
        for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++)
                target[i] = c;
        if (c == '\n')
                target[i++] = c;
        target[i] = '\0';
        return i;
}

/* Returns the index of term in sentence, -1 if not found */
int strindex(const char *term, const char *sentence) {
        for (int i = 0; sentence[i] != '\0'; i++) {
                int k = 0;
                for (int j = i; sentence[j] == term[k]; j++, k++);
                if (k > 0 && term[k] == '\0')
                        return i;
        }
        return -1;
}
