void printOutput(int col, int row, char formula[]);
int power(int base, int top);
void copy(int col, int current[], const int last[]);
void flip(int col, int i, int table[]);
void push(int element);
int pop();
void clear();
int getSize();
void runFormula(int var[], char formula[], int output[]);
int findOps(const char formula[]);
int findIndex(char val);
int findVar(const char formula[]);