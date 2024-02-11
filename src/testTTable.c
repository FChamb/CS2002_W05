#include <stdio.h>
#include "ttable.h"
#include "testTTable.h"

/**
 * Test the copy function which copies all of the values
 * from one array to another.
*/
void testCopy() {
    int passed = 1;
    printf("Testing copy functionality...\n");
    int col = 10;
    int current[col];
    int last[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    copy(col, current, last);
    for (int i = 0; i < col; i++) {
        if (current[i] != last[i]) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, last[i]);
            passed = 0;
        }
    }
    if (passed == 1) {
        printf("Testing of copy passed.\n");
    }
}

/**
 * Test the flip function which flips each value
 * in the provided array to a new value.
*/
void testFlip() {
    int passed = 1;
    printf("Testing flip functionality...\n");
    int col = 4;
    int last = col - 1;
    int table[] = {0, 1, 0, 1};
    int expected[] = {0, 1, 1, 0};
    flip(col, last, table);
    for (int i = 0; i < col; i++) {
        if (table[i] != expected[i]) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, expected[i]);
            passed = 0;
        }
    }
    if (passed == 1) {
        printf("Testing of flip passed.\n");
    }
}

/**
 * Test the power function which raises a base value to
 * a provided top value and returns the result.
*/
void testPower() {
    int passed = 1;
    printf("Testing power functionality...\n");
    int base = 2;
    int output[10];
    int expected[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    for (int i = 0; i < 10; i++) {
        output[i] = power(base, i + 1);
    }
    for (int i = 0; i < 10; i++) {
        if (output[i] != expected[i]) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, expected[i]);
            passed = 0;
        }
    }
    if (passed == 1) {
        printf("Testing of power passed.\n");
    }
}

/**
 * Test the pop function which gets the top value to the stack.
 * First checks pop up to max size of stack. Then ensures
 * future pops don't work.
*/
void testPop() {
    int passed = 1;
    printf("Testing pop functionality...\n");
    for (int i = 0; i < 1000; i++) {
        push(i);
    }
    for (int i = 999; i >= 0; i--) {
        if (i != pop()) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, i);
            passed = 0;
        }
    }
    int errorExpected = -1;
    int overPop = pop();
    if (overPop != errorExpected) {
        printf("Test failed @ (Index, Value): (%d,%d)\n", overPop, overPop);
        passed = 0;
    }
    if (passed == 1) {
        printf("Testing of pop passed.\n");
    }
}

/**
 * Test the push function which pushes a value to the stack.
 * First checks pushing up to max size of stack. Then ensures
 * future pushes don't work.
*/
void testPush() {
    int passed = 1;
    printf("Testing push functionality...\n");
    for (int i = 0; i < 1000; i++) {
        push(i);
    }
    int overPush = 1001;
    push(overPush);
    if (overPush == pop()) {
        printf("Test failed @ (Index, Value): (%d,%d)\n", overPush, overPush);
        passed = 0;
    }
    for (int i = 998; i >= 0; i--) {
        if (i != pop()) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, i);
            passed = 0;
        }
    }
    if (passed == 1) {
        printf("Testing of push passed.\n");
    }
}

/**
 * Test the clear function which clears all values in the stack.
 * First checks clearing up to max size of stack. Then ensures
 * the stack is empty.
*/
void testClear() {
    int passed = 1;
    printf("Testing clear functionality...\n");
    for (int i = 0; i < 1000; i++) {
        push(i);
    }
    clear();
    int size = getSize();
    if (size != 0) {
        printf("Test failed\n");
        passed = 0;
    }
    if (passed == 1) {
        printf("Testing of clear passed.\n");
    }
}

/**
 * Test runFormula function by providing a specific row for
 * calculation and ensuring the output result is correct.
 */
void testRunFormula() {
    int passed = 1;
    printf("Testing runFormula functionality...\n");
    int var[] = {0, 0, 1, 1, 0};
    char formula[] = "abcde&&&&";
    int output[5];
    int expected[] = {0, 0, 0, 0, 0};
    runFormula(var, formula, output);
    for (int i = 0; i < 5; i++) {
        if (output[i] != expected[i]) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, expected[i]);
            passed = 0;
        }
    }
    int var2[] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    char formula2[] = "abcdefghij&&&&&&&&&";
    int output2[10];
    int expected2[] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    runFormula(var2, formula2, output2);
    for (int i = 0; i < 10; i++) {
        if (output2[i] != expected2[i]) {
            printf("Test failed @ (Index, Value): (%d,%d)\n", i, expected2[i]);
            passed = 0;
        }
    }
    if (passed == 1) {
        printf("Testing of runFormula passed.\n");
    }
}

/**
 * Test findOps function by providing random formulas and ensuring
 * the number returned is valid.
*/
void testFindOps() {
    int passed = 1;
    printf("Testing findOps functionality...\n");
    char formula[] = "abcdefg&|->#=";
    int expected = 6;
    if (findOps(formula) != expected) {
        printf("Test failed @ (Formula, Value): (%s,%d)\n", formula, expected);
        passed = 0;
    }
    char formula2[] = "ab&-c>";
    int expected2 = 3;
    if (findOps(formula2) != expected2) {
        printf("Test failed @ (Formula, Value): (%s,%d)\n", formula2, expected2);
        passed = 0;
    }
    char formula3[] = "a-bc&&de|#";
    int expected3 = 5;
    if (findOps(formula3) != expected3) {
        printf("Test failed @ (Formula, Value): (%s,%d)\n", formula3, expected3);
        passed = 0;
    }
    if (passed == 1) {
        printf("Testing of findOps passed.\n");
    }
}

/**
 * Test findIndex function by providing several different letters of the
 * alphabet to ensure all return the correct index.
*/
void testFindIndex() {
    int passed = 1;
    printf("Testing findOps functionality...\n");
    char val = 'a';
    int expected = 0;
    if (findIndex(val) != expected) {
        printf("Test failed @ (Letter, Value): (%c,%d)\n", val, expected);
        passed = 0;
    }
    char val2 = 'h';
    int expected2 = 07;
    if (findIndex(val2) != expected2) {
        printf("Test failed @ (Letter, Value): (%c,%d)\n", val2, expected2);
        passed = 0;
    }
    char val3 = 'z';
    int expected3 = 25;
    if (findIndex(val3) != expected3) {
        printf("Test failed @ (Letter, Value): (%c,%d)\n", val3, expected3);
        passed = 0;
    }
    char val4 = '^';
    int expected4 = -1;
    if (findIndex(val4) != expected4) {
        printf("Test failed @ (Letter, Value): (%c,%d)\n", val4, expected4);
        passed = 0;
    }
    if (passed == 1) {
        printf("Testing of findOps passed.\n");
    }
}

int main() {
    printf("Beginning tests...\n");
    printf("-------------------------------------------------------------------------\n");
    testCopy();
    printf("-------------------------------------------------------------------------\n");
    testFlip();
    printf("-------------------------------------------------------------------------\n");
    testPower();
    printf("-------------------------------------------------------------------------\n");
    testPop();
    printf("-------------------------------------------------------------------------\n");
    testPush();
    printf("-------------------------------------------------------------------------\n");
    testClear();
    printf("-------------------------------------------------------------------------\n");
    testRunFormula();
    printf("-------------------------------------------------------------------------\n");
    testFindOps();
    printf("-------------------------------------------------------------------------\n");
    testFindIndex();
    printf("-------------------------------------------------------------------------\n");
    printf("Ending tests...\n");
}