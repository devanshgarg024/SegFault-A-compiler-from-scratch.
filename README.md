# Building a compiler consisting of a lexer->parser->code generator.

GOAL of project: This a completely learning based project. To build a compiler from scratch without using the library functions. 
1. The end goal of the compiler is to be able to implement FizzBuzz on its own.
2. This will include implementation of loops and conditional statements.
3. This will also include a basic implementation of arithmetic operators.
4. Also an implementation of the modulo operator.

Current progress: Can compile a fizzbuzz code given in the examples!

Dependencies: nasm, gcc

Build Instructions part-I: 
1. gcc main.c parserf.c lexerf.c codegeneratorf.c ./hashmap/hashmapoperators.c -c
2. gcc main.o parserf.o lexerf.o codegeneratorf.o hashmapoperators.o -o demo
3. ./demo examples/fizzbuzz.did output
4. ./output

Build Instructions part-II:
1. ./build.sh
2. ./build examples/fizzbuzz.did output
3. ./output

NOTE: This compiler uses x86 architecture and the code will not compile if you are using arm64 based architectures. To deal with this problem, here is a link: https://mrsen.medium.com/how-to-run-x86-assembly-on-m1-mac-on-docker-a58c476c6655


PS: This could not have been possible without CobbCoding's video series on the compiler from scratch: https://www.youtube.com/watch?v=-4RmhDy0A2s&list=PLRnI_2_ZWhtA_ZAzEa8uJF8wgGF0HjjEz&ab_channel=CobbCoding

Also yes, a lot of segmentation faults were dealt with in this, hence the name :p.
