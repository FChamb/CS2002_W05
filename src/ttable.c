#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttable.h"
#define maxSize 26;

static char stack[];
static int max = maxSize;
static int size;
static int numOperators;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    int col;
    sscanf(argv[1], "%d", &col);
    int row = power(2, col);
    char *formula = argv[2];
    findOps(argv);
    int table[row][col];
    genTable(row, col, table);

    //for (int i = 0; i < row; i++) {
        //runFormula(table[i], formula, col);
    //}
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            //runFormula(table[i], formula, col);
            printf("%d ", table[j][i]);
        }
        printf("\n");
    }

    return 0;
}

void genTable(int row, int col, int table[row][col]) {
    for (int i = 0; i < col; i++) {
        table[0][i] = 0;
    }

    for (int i = 1; i < (row); i++) {
        copy(col, table[i], table[i - 1]);
        flip(col, col - 1, table[i]);
    }
}

void copy(int col, int current[col], const int last[col]) {
    for (int i = 0; i < col; i++) {
        current[i] = last[i];
    }
}

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

int power(int base, int top) {
    int new = base;
    for (int i = 0; i < top - 1; i++) {
        new *= base;
    }
    return new;
}

void push(char element) {
    if (size < max) {
        if (size > 0) {
            stack[size] = element;
            size++;
        }
    }
}

char pop() {
    if (size == 0) {
        return -1;
    } else {
        return stack[size--];
    }
}

void clear() {
    size = 0;
}

void runFormula(int var[], char formula[], int col) {
    clear();
    for (int i = 0; i < strlen(formula); i++) {
        if (isalpha(formula[i])) {
            push(formula[i]);
        } else {
            if (formula[i] == '-') {
                char operand = pop();
                char result;
                if (operand == 'i') {
                    result = '0';
                } else {
                    result = '1';
                }
                push(result);
            } else if (formula[i] == '>') {
                char operand2 = pop();
                char operand1 = pop();
                char result;
                if (operand1 == '0' || operand2 == '1') {
                    result = '1';
                } else {
                    result = '0';
                }
                push(result);
            } else {
                char operand2 = pop();
                char operand1 = pop();
                char result;
                switch (formula[i]) {
                    case '&':
                        result = (operand1 == '1' && operand2 == '1') ? '1' : '0';
                        break;
                    case '|':
                        result = (operand1 == '1' && operand2 == '1') ? '1' : '0';
                        break;
                    case '=':
                        result = (operand1 == operand2) ? '1' : '0';
                        break;
                    case '#':
                        result = (operand1 != operand2) ? '1' : '0';
                        break;
                    default:
                        printf("Error: Invalid Formula!\n");
                        exit(1);
                }
                push(result);
            }
        }
    }
    printf("%d", var[0]);
    for (int i = 1; i < col; i++) {
        printf(" %d", var[i]);
    }
    printf(" : %s : %c\n", formula, pop());
}

void findOps(char formula[]) {
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!isalpha(formula[i])) {
            numOperators++;
        }
    }
}