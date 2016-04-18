

test : test.o utils.o
	gcc -o test test.o utils.o -g


test.o : test.c utils.h
	gcc -c test.c utils.h -g

utils.o :  utils.c utils.h
	gcc -c utils.c utils.h -g


clean :
	-rm *.o test
