#include <stdio.h>
#include <string.h>
#include "ttable.h"

static int max = 1000;

/**
 * The main method of the program is the starting point of the program. The command
 * line arguments are provided to the program here. Several checks ensure the provided
 * arguments are valid. First a check ensures that only three value were provided. Another
 * check grabs the first argument and ensures that the number of provided variables is greater
 * than one and does not exceed 26 as per the specification. The last check grabs the second
 * argument and checks that the formula provided does not exceed a max length of 1000 per the
 * spec. A call to printOutput is called at the end. Finally 0 is returned at the end upon
 * successful completion.
 * @param argc number of arguments provided
 * @param argv array of the command arguments when run
 * @return int - 0 for successful, 1 for failure
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <numberOfVariables> <'formula'>\n", argv[0]);
        return 1;
    }

    int col;
    sscanf(argv[1], "%d", &col);
    if (col < 1 || col > 26) {
        printf("Error: Number of variables should be between 1 and 26!\n");
        return 1;
    }

    int row = power(2, col);
    char *formula = argv[2];
    if (strlen(formula) > max) {
        printf("Error: Formula length exceeds maximum allowed length!\n");
        return 1;
    }

    int numVariables = findVar(formula);
    if (numVariables > col) {
        printf("Error: Formula contains more variables then specified!\n");
        return 1;
    }

    printOutput(col, row, formula);
    return 0;
}