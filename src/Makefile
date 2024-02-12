all : ttable tests parttwo

ttable : ttable.o ttableFunctions.o
	clang ttable.o ttableFunctions.o -o ttable -Wall -Wextra -g

ttable.o : ttable.c
	clang ttable.c -c -o ttable.o -Wall -Wextra -g

ttableFunctions.o : ttableFunctions.c ttableFunctions.h
	clang ttableFunctions.c -c -o ttableFunctions.o -Wall -Wextra -g

tests : testTTable.o ttableFunctions.o
	clang testTTable.o ttableFunctions.o -o tests -Wall -Wextra -g

testTTable.o : testTTable.c testTTable.h
	clang testTTable.c -c -o testTTable.o -Wall -Wextra -g

parttwo : partTwo.o ttableFunctions.o
	clang partTwo.o ttableFunctions.o -o parttwo -Wall -Wextra -g

partTwo.o : partTwo.c
	clang partTwo.c -c -o partTwo.o -Wall -Wextra -g

clean :
	rm *.o ttable tests parttwo