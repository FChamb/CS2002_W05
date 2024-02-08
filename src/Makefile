all : stage1

stage1 : ttable.o
	clang ttable.o -o ttable -Wall -Wextra -g

ttable.o : ttable.c ttable.h
	clang ttable.c -c -o ttable.o -Wall -Wextra -g

clean :
	rm *.o ttable