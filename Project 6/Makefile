CFLAGS=-g -std=c99 -O3 -m32 -Werror -Wall

main : main.o sim.o Makefile
	gcc $(CFLAGS) -o main main.o sim.o

%.o : %.c Makefile
	gcc $(CFLAGS) -MD -c $*.c

run : neg.out max.out fact.out

test : run neg.res max.res fact.res

neg.out : Makefile main
	-./main -p 'x0-x.neg' -100 > neg.out 2>&1
	-./main -p 'x0-x.neg' 10 >> neg.out 2>&1

max.out : Makefile main
	-./main -p '0s1s2s1l2l-19>1l0l.2l0l.max'  10 20 > max.out 2>&1
	-./main -p '0s1s2s1l2l-19>1l0l.2l0l.max'  -10 -20 >> max.out 2>&1
	-./main -p '0s1s2s1l2l-19>1l0l.2l0l.max'  -20 -10 >> max.out 2>&1
	-./main -p '0s1s2s1l2l-19>1l0l.2l0l.max'  20 10 >> max.out 2>&1

fact.out : Makefile main
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 0 > fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 1 >> fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 2 >> fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 3 >> fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 4 >> fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 5 >> fact.out 2>&1
	-./main -p 'xd8>p1x.d1x-0c*x.fact' 6 >> fact.out 2>&1

%.res : Makefile
	@((diff -bwB $*.ok $*.out > /dev/null 2>&1) && echo "$* : PASS") || (echo "$* : FAIL"; echo '+----------+'; echo "| expected |"; echo "+----------+"; cat $*.ok; echo '+-------+'; echo "| found |"; echo '+-------+'; cat $*.out)

clean :
	rm -f *.d
	rm -f *.o
	rm -f main
	rm -f *.out

-include *.d
