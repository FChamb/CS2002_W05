#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttable.h"

/**
 * These are the global variables for the file. The stack which is used to
 * define operation order on the provided formula is defined with a max size
 * of 1000 according to the specification. A max variable is defined for future
 * use and the current size of the stack is initialized to 0.
 */
static int stack[1000];
static int max = 1000;
static int size = 0;

/**
 * printOutput contains all of the logic to print out the specification accurate
 * table. This program first defines an output array for the logic portion of the
 * table. A for loop prints every letter starting at a up to the number provided.
 * Then the format to the rest of the header is printed. A lastTable variable is
 * created to store the values from the previous row. A for loop counts up from 0
 * to the number of rows for a given table. At each stop an array is created to represent
 * the row and a for loop either fills the array with 0's if it is the first time or
 * copies the previous array and performs a flip on the row. Then runFormula is called
 * which calculates the value for the provided formula in a given row with the output being
 * put into the output array. A for loop then prints every value for the individual variables.
 * Another for loop goes through every value in the formula. If the character at each stop is a
 * letter than a space is printed, otherwise the correct value from the output array is printed.
 * Lastly the result column is printed, the current row for variables is copied into the lastRow
 * array and the process repeats.
 * @param col number of columns for the table (i.e. # of variables)
 * @param row number of rows for the table (i.e two to the power of the # of variables)
 * @param formula the string formula in RPN provided by the user
 */
void printOutput(int col, int row, char formula[]) {
    int output[findOps(formula) + 1];
    // Print the 'a b c...etc for the header
    for (int i = 0; i < col; i++) {
        printf("%c ", 'a' + i);
    }
    // Print the : <formula> : Result section of header followed by line of ===...
    printf(": %s : Result\n", formula);
    for (int i = 0; i < ((col * 2) + strlen(formula) + 11); i++) {
        printf("=");
    }
    printf("\n");
    int lastTable[col];
    // Used to fill out and print each row of the table
    for (int i = 0; i < (row); i++) {
        int table[col];
        if (i == 0) {
            for (int k = 0; k < col; k++) {
                table[k] = 0;
            }
        }
        if (i >= 1) {
            copy(col, table, lastTable);
            flip(col, col - 1, table);
        }
        runFormula(table, formula, output);
        for (int j = 0; j < col; j++) {
            printf("%d ", table[j]);
        }
        printf(": ");
        int outIndex = 0;
        for (int k = 0; k < strlen(formula); k++) {
            if (!isalpha(formula[k]) && formula[k] != '0' && formula[k] != '1') {
                printf("%d", output[outIndex++]);
            } else {
                printf(" ");
            }
        }
        printf(" :   %d", output[outIndex]);
        printf("\n");
        copy(col, lastTable, table);
    }
}

/**
 * Copy takes a length, col, the current array and the last array. A for
 * loop cycles through every value in the last array and copies the values
 * into the current array.
 * @param col the number of variables or length of the array
 * @param current the current array to be adjusted
 * @param last the last array to be copied
 */
void copy(int col, int current[], const int last[]) {
    for (int i = 0; i < col; i++) {
        current[i] = last[i];
    }
}

/**
 * Flip takes a length, col, the last value in the current row
 * and the row array. A if statement checks if the last value is a
 * zero. If it is, then the value is set to one. The rest of the
 * row is set to zeros. If the value is not zero, a recursive call
 * passes all the same values, except the second to last value.
 * @param col the number of variables or length of the array
 * @param last the last index of the previous item in the array
 * @param table the current row in the truth table
 */
void flip(int col, int last, int table[]) {
    if (table[last] == 0) {
        table[last] = 1;
        for (int i = last + 1; i < col; i++) {
            table[i] = 0;
        }
    } else {
        flip(col, last - 1, table);
    }
}

/**
 * Power is a simple function which takes a base and top value.
 * The base value is multiplied by itself the number of times as
 * top and then returned.
 * @param base the value to be multiplied
 * @param top the number of multiplications
 * @return new the final result
 */
int power(int base, int top) {
    int new = base;
    for (int i = 0; i < top - 1; i++) {
        new *= base;
    }
    return new;
}

/**
 * Push is a function for the stack. It takes an integer element.
 * The size of the stack is checked to ensure it is not larger than
 * the maximum number of values allowed. The element is added to the
 * stack at the current size spot and the size increases by one.
 * @param element the value to be added to the stack
 */
void push(int element) {
    if (size < max) {
        if (size >= 0) {
            stack[size] = element;
            size++;
        }
    }
}

/**
 * Pop is a function for the stack. If the size is equal to 0, there
 * is nothing in the stack and the function returns -1. Otherwise the
 * stack returns the current element at the size and then subtracts the size
 * by one.
 * @return the element at the top of the stack
 */
int pop() {
    if (size == 0) {
        return -1;
    } else {
        return stack[--size];
    }
}

/**
 * Clear sets the size of the stack to 0, therein making
 * every value unobtainable.
 */
void clear() {
    size = 0;
}

/**
 * Get size is not used in the implementation of this project.
 * It exists purely to test stack implementation.
 * @return size of the stack
 */
int getSize() {
    return size;
}

/**
 * runFormula calculates the True and False values for every operator in
 * the formula for a given row. The var array represents the current row.
 * The formula array represents the string value of the formula. The output
 * array is where the final calculations are put. The function firstly clears
 * the stack. Then a output index is created and set to 0. A for loop cycles
 * through every value in the formula string. If the current character is a
 * letter or a 0 or 1 then it enters the first half of the conditional statement.
 * If the value is 0 or 1 it is pushed into the stack for calculation. If the
 * value is a letter its index/position is found and its value is pushed. If the
 * value in the formula is an operator then a switch case determines which one it
 * is. For each operator the appropriate case is entered. The number of values needed
 * are popped from the stack. And used to find the result. If the object does not match
 * a valid symbol the default case is entered and the appropriate message is printed
 * while terminating the program. Lastly the output array is added the result. The result
 * is pushed into the stack for future calculations. And if the current item is the last the
 * result is added one more time to represent the Result: column.
 * @param var represents the current row
 * @param formula represents the string value of the formula
 * @param output the array where the final calculations are put
 */
void runFormula(int var[], char formula[], int output[]) {
    clear();
    int outIndex = 0;
    if (strlen(formula) == 1 && (isalpha(formula[0]) || formula[0] == '1' || formula[0] == '0')) {
        output[0] = var[0];
    } else {
        for (int i = 0; i < strlen(formula); i++) {
            if (isalpha(formula[i]) || formula[i] == '0' || formula[i] == '1') {
                if (formula[i] == '0' || formula[i] == '1') {
                    if (formula[i] == '0') {
                        push(0);
                    } else {
                        push(1);
                    }
                } else {
                    int index = findIndex(formula[i]);
                    push(var[index]);

                }
            } else {
                int result;
                int opp1;
                int opp2;
                switch (formula[i]) {
                    case '-':
                        result = (pop() == 0) ? 1 : 0;
                        break;
                    case '&':
                        opp1 = pop();
                        opp2 = pop();
                        result = (opp1 == 1 && opp2 == 1) ? 1: 0;
                        break;
                    case '|':
                        opp1 = pop();
                        opp2 = pop();
                        result = (opp1 == 1 || opp2 == 1) ? 1 : 0;
                        break;
                    case '=':
                        opp1 = pop();
                        opp2 = pop();
                        result = (opp1 == opp2) ? 1 : 0;
                        break;
                    case '>':
                        opp1 = pop();
                        opp2 = pop();
                        result = (opp2 == 0 || opp1 == 1) ? 1 : 0;
                        break;
                    case '#':
                        opp1 = pop();
                        opp2 = pop();
                        result = (opp1 != opp2) ? 1 : 0;
                        break;
                    default:
                        printf("Error: Invalid Formula!\n");
                        exit(1);
                }
                output[outIndex++] = result;
                push(result);
                if (i == strlen(formula) - 1) {
                    output[outIndex++] = result;
                }
            }
        }
    }
}

/**
 * findOps takes the formula and uses a for loop to determine whether
 * each character in the formula is a letter, 0 or 1. If it is not,
 * it is a operator and the count increases. At the end this count is returned.
 * @param formula the string representation of the formula
 * @return numOperators the count of operators in the formula
 */
int findOps(const char formula[]) {
    int numOperators = 0;
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!isalpha(formula[i]) && formula[i] != '0' && formula[i] != '1') {
            numOperators++;
        }
    }
    return numOperators;
}

/**
 * findIndex takes a specific character. A for loop counts up to 26 and if the value
 * is equal to 'a' plus the index than the index is returned. Otherwise -1 is returned
 * @param val the character value to be searched
 * @return the index of the character in the alphabet
 */
int findIndex(char val) {
    for (int i = 0; i < 26; i++) {
        if (val == 'a' + i) {
            return i;
        }
    }
    return -1;
}

/**
 * findVar takes the provided formula and counts the number of variables or letters
 * found without counting duplicates.
 * @param formula the string representation of the formula
 * @return numVariables the count of variables in the formula
 */
int findVar(const char formula[]) {
    char found[26];
    for (int i = 0; i < 26; i++) {
        found[i] = '0';
    }
    for (int i = 0; i < strlen(formula); i++) {
        if (isalpha(formula[i])) {
            for (int j = 0; 26; j++) {
                if (found[j] == '0') {
                    found[j] = formula[i];
                }
                if (formula[i] == found[j]) {
                    break;
                }
            }
        }
    }
    for (int i = 26; i > 0; i--) {
        if (found[i - 1] != '0') {
            return i;
        }
    }
    return 0;
}