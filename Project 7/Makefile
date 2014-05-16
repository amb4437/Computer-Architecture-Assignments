CFLAGS=-g -std=c99 -O3 -m32 -Werror -Wall

main : main.o fast.o Makefile
	gcc $(CFLAGS) -o main main.o fast.o

%.o : %.c Makefile
	gcc $(CFLAGS) -MD -c $*.c

run : main
	./main

test : run

clean :
	rm -f *.d
	rm -f *.o
	rm -f main

-include *.d
