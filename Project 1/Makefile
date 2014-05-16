main : main.o
	gcc -m32 -o main main.o

main.o : main.s
	gcc -m32 -c main.s

test.ok: test.in tr.sh
	cat test.in | sh ./tr.sh  > test.ok

test.out : main test.in
	cat test.in | ./main > test.out
	
test : test.ok test.out
	@((diff -wB test.ok test.out > /dev/null 2>&1) && echo "Pass") || (echo "Fail"; echo "\nExpected\n"; cat test.ok; echo "\nFound\n"; cat test.out; echo "\n")

clean :
	rm -f test.ok test.out
	rm -f *.o
	rm main
