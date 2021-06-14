#include <stdio.h>

enum State {
        IN, OUT
};


/*
   Counts the number of lines, words, and characters in standard input.
   Output can be checked against the Unix 'wc' program.
   From 'The C Programming Language' by Kernighan and Ritchie.
 */

int main(int argc, const char *argv[]) {
        long int n_chars = 0;
        long int n_words = 0;
        long int n_lines = 0;
        
        /* Indicates whether currently inside or outside a word */
        int state = OUT;
        int c;
        
        while ((c = getchar()) != EOF) {
                ++n_chars;
                /* Newline characters indicate a line is over */
                if (c == '\n')
                        ++n_lines;
                /* Whitespace of any kind indicates that we are outside a word.
                   If the current character is not whitespace and the state was 'OUT',
                   we have entered a new word. */
                if (c == ' ' || c == '\t' || c == '\n')
                        state = OUT;
                else if (state == OUT) {
                        state = IN;
                        ++n_words;
                }
        }

        printf("%ld %ld %ld\n", n_lines, n_words, n_chars);

        return 0;
}
