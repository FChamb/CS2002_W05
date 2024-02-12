#include <stdio.h>
#include <string.h>
#include "ttable.h"

int main() {
    // Run the output for question one in Part 2 (De Morgan's Law)
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("To prove De Morgan's Law we will insert the entire provided formula into the\n");
    printf("./ttable generator. If the output is a tautology the formula is valid, therein\n");
    printf("proving the law is correct.\n");
    int col1 = 4;
    int row1 = power(2, col1);
    char formula1[] = "ab|cd||-a-b-&c-d-&&=";
    printOutput(col1, row1, formula1);
    printf("Every row in the table is equal to one, or true, therein making this a tautology and\n");
    printf("the law correct.\n");

    // Run the output for question two in Part 2 (Ian & Chris's unfair game)
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("To show the outcome of Ian and Chris's game we start by defining the variables\n");
    printf("We will let a be heads, b for tails. If a is correct then Chris wins and if b is\n");
    printf("correct then Ian loses\n");
    int col2 = 2;
    int row2 = power(2, col2);
    char formula2[] = "ab|ab&#";
    printOutput(col2, row2, formula2);
    printf("\n");
    printf("\n");
    //ab#ac->&
    return 0;
}