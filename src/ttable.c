#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttable.h"
#define maxSize 26;

static int stack[26];
static int max = maxSize;
static int size = 0;
static char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    int col;
    sscanf(argv[1], "%d", &col);
    int row = power(2, col);
    char *formula = argv[2];
    int table[row][col];
    genTable(row, col, table);
    int output[findOps(*argv)];


    for (int i = 0; i < col; i++) {
        printf("%c ", alphabet[i]);
    }
    printf(": %s : Result\n", formula);
    for (int i = 0; i < ((col * 2) + strlen(formula) + 11); i++) {
        printf("=");
    }
    printf("\n");
    for (int i = 0; i < row; i++) {
        runFormula(table[i], formula, output);
        for (int j = 0; j < col; j++) {
            printf("%d ", table[i][j]);
        }
        printf(": ");
        for (int k = 0; k < col; k++) {
            printf("%d ", output[k]);
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
        return stack[size--];
    }
}

void clear() {
    size = 0;
}

void runFormula(int var[], char formula[], int output[]) {
    clear();
    for (int i = 0; i < strlen(formula); i++) {
        if (isalpha(formula[i])) {
            int index = findIndex(formula[i]);
            push(var[index]);
            printf("a%db%d ", stack[0], stack[1]);
        } else {
            int result;
            switch (formula[i]) {
                case '-':
                    result = (pop() == '0') ? 1 : 0;
                    break;
                case '&':
                    result = add(pop(), pop());
                    break;
                case '|':
                    result = (pop() == '1' && pop() == '1') ? 1 : 0;
                    break;
                case '=':
                    result = (pop() == pop()) ? 1 : 0;
                    break;
                case '>':
                    result = (pop() == '0' || pop() == '1') ? 1 : 0;
                    break;
                case '#':
                    result = (pop() != pop()) ? 1 : 0;
                    break;
                default:
                    printf("Error: Invalid Formula!\n");
                    exit(1);
            }
            output[i] = result;
            //printf("result%d", result);
        }
    }
}

int add(int a, int b) {
    //printf("a%db%d", a, b);
    if (a == '1' && b == '1') {
        return 1;
    } else {
        return 0;
    }
}

int findOps(const char formula[]) {
    int numOperators = 0;
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!isalpha(formula[i])) {
            numOperators++;
        }
    }
    return numOperators;
}

int findIndex(char val) {
    for (int i = 0; i < 26; i++) {
        if (val == alphabet[i]) {
            return i;
        }
    }
}