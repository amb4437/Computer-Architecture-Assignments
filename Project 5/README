Due: Monday 3/3/2014 @ 11:59pm

Objective:
~~~~~~~~~~

Learn how to develop a functional simulator

Assignment:
~~~~~~~~~~~

Finish the Java implementation of a functional simulator for a simple
instruction set architecture.

The instruction set architecture:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Our architecture has:

   - 4 8-bit registers R0, R1, R2, and R3
   - an 8-bit PC
   - an 8-bit result register

All registers are initialized to 0.

Instructions are either 1 or 2 byte long. Here are the defined instructions:

binary encoding    instruction           description

00000000           halt                  stop the processor

000011dd           jle Rdd               branch to the address in Rdd if the
                                         value in the result register is less
                                         than or equal to zero
                                    
000110dd           outch Rdd             print the character whose ASCII
                                         code is in Rdd

000111dd           show Rdd              print the value in Rdd as both
                                         hexadecimal and decimal integer

001000dd vvvvvvvv  movi vvvvvvvv,Rdd     move the 8 bit immediate value
                                         vvvvvvvv to Rdd

1000ssdd           add Rss,Rdd           add the contents of Rss and Rdd and
                                         store the result in Rdd

1011ssdd           cmp Rss,Rdd           subtract the contents of Rss from Rdd
                                         and store the result in the result
                                         register

The simulator terminates if it encounters an invalid instruction

To compile:
~~~~~~~~~~~

make


To run:
~~~~~~~

make test

File:
~~~~~

src/cs429/Main.java         The main program  (don't change it)
test.ok                     Expected output (don't change it)
src/cs429/Simulator.java    The simulator
test.out                    The output produced by running "make test"
