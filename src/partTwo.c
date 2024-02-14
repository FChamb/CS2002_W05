#include <stdio.h>
#include "ttable.h"

int main() {
    // Run the output for question one in Part 2 (De Morgan's Law)
    printf("--------------------------------------------------------------------------------------------------\n");
    int col1 = 4;
    int row1 = power(2, col1);
    char formula1[] = "ab|cd||-a-b-&c-d-&&=";
    printf("Question 1: ./ttable %d %s\n", col1, formula1);
    printOutput(col1, row1, formula1);

    // Run the output for question two in Part 2 (Ian & Chris's unfair game)
    printf("--------------------------------------------------------------------------------------------------\n");
    int col2 = 2;
    int row2 = power(2, col2);
    char formula2[] = "ab>a-b>|";
    printf("Question 2: ./ttable %d %s\n", col2, formula2);
    printOutput(col2, row2, formula2);

    // Run the output for question three in Part 2 (A dinner party)
    printf("--------------------------------------------------------------------------------------------------\n");
    int col3 = 5;
    int row3 = power(2, col3);
    char formula3[] = "dc|be#&ab>&ed=&cad&>&";
    printf("Question 3: ./ttable %d %s\n", col3, formula3);
    printOutput(col3, row3, formula3);

    // Run the output for question four in Part 2 (Which box is it?)
    printf("--------------------------------------------------------------------------------------------------\n");
    int col4 = 9;
    int row4 = power(2, col4);
    char formula4[] = "da>ea>&fh>&ga->&ha->&hh->&aaa-#>&baa-#>&chh->&ab#c#&de#f#&gh#i#&ad-g-&b-&c-&>&da-g-&e-&f-&>&ga-d-&h-&i-&>&be-h-&a-&c-&>&eb-h-&d-&f-&>&hb-e-&g-&i-&>&cf-i-&a-&b-&>&fc-i-&d-&e-&>&ic-f-&g-&h-&>&";
    printf("Question 4: ./ttable %d %s\n", col4, formula4);
    printOutput(col4, row4, formula4);

    return 0;
}