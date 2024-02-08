int power(int col, int i);
void genTable(int row, int col, int table[row][col]);
void copy(int col, int current[col], const int last[col]);
void flip(int col, int i, int table[]);
void push(char element);
char pop();
void clear();
void runFormula(int var[], char formula[]);
void findOps(char formula[]);