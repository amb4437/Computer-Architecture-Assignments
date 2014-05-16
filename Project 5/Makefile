
all :
	rm -rf classes
	mkdir classes
	javac -d classes src/cs429/*.java

test: all
	java -cp classes cs429.Main > test.out
	@echo "comparing results"
	@(diff -bwB test.out test.ok > /dev/null 2>&1 && echo "pass") || diff -b test.out test.ok

clean:
	rm -rf classes
	rm test.out
