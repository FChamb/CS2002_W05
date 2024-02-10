#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttable.h"

static int stack[1000];
static int max = 1000;
static int size = 0;

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
    if (strlen(formula) >= 1000) {
        printf("Error: Formula length exceeds maximum allowed length!\n");
        return 1;
    }

    int output[findOps(formula) + 1];
    for (int i = 0; i < col; i++) {
        printf("%c ", 'a' + i);
    }
    printf(": %s : Result\n", formula);
    for (int i = 0; i < ((col * 2) + strlen(formula) + 11); i++) {
        printf("=");
    }
    printf("\n");
    int lastTable[col];
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
    return 0;
}

void copy(int col, int current[], const int last[]) {
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

void push(int element) {
    if (size < max) {
        if (size >= 0) {
            stack[size] = element;
            size++;
        }
    }
}

int pop() {
    if (size == 0) {
        return -1;
    } else {
        return stack[--size];
    }
}

void clear() {
    size = 0;
}

void runFormula(int var[], char formula[], int output[]) {
    clear();
    int outIndex = 0;
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
                if (i == strlen(formula) - 1) {
                    output[outIndex++] = var[index];
                }
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

int findOps(const char formula[]) {
    int numOperators = 0;
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!isalpha(formula[i]) && formula[i] != '0' && formula[i] != '1') {
            numOperators++;
        }
    }
    return numOperators;
}

int findIndex(char val) {
    for (int i = 0; i < 26; i++) {
        if (val == 'a' + i) {
            return i;
        }
    }
    return -1;
}