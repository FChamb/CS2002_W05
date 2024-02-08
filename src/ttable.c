#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttable.h"

static char stack[];
static int maxSize;
static int size;
static int numOperators;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments!\n");
        return 1;
    }
    int col;
    sscanf(argv[1], "%d", &col);
    int row = power(col, 2);
    findOps(argv, argc);
    int table[row][col];
    genTable(row, col, table);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            runFormula(table[i]);
            printf("%d ", table[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");

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
        table[last + 1] = 1;
        for (int i = last; i < col; i++) {
            table[i] = 0;
        }
    } else {
        flip(col, last, table);
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
    if (size < maxSize) {
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

void runFormula(int var[], char formula[]) {

}

void findOps(char formula[]) {
    for (int i = 0; i < sizeof(formula) - 2; i++) {
        if (!isalpha(formula[i])) {
            numOperators++;
        }
    }
}