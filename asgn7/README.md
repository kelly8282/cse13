# Assignment 7: The Great Firewall of Santa Cruz

## Description
In this program, we are making a program that uses bloom filters and hash tables in order to filter out offensive words.

## Building
Run this command to compile the program
```
$ make all
```

## Running/Instructions
Run this command to test/see the followings.
```
$ ./banhammer
```
You can run whatever command you wish after the following code above. Note: -h will give you a menu.

## File Included
parser.c- A source file for implementing my regex parsing module.
parser.h- A header file that defines the interface for parser.c.
bv.c- A source file for implementing my bit vector ADT.
bv.h- A header file that defines the interface for bv.c.
bf.c- A source file for implementing my Bloom filter ADT.
bf.h- A header file that defines the interface for bf.c.
banhammer.c- A source file that has my main function. 
messages.h- A header file for my banhammer.c file.
salts.h- A header file that defines my mixspeak,secondary, and tertiary salts functions.
speck.c- A source file for implementing my SPECK cipher.
speck.h- A header file that defines the interface for speck.c.
ht.c- A source file for implementing my hash table ADT.
ht.h- A header file that defines the interface for ht.c.
bst.c- A source file for implementing my binary search tree ADT.
bst.h- A header file that defines the interface for bst.c.
node.c- A source file for implementing my node ADT.
node.h- A header file that defines the interface for node.c.
Makefile- This allows us to use clang and compile our program.
README.md- In markdown format, it tells us how to run the program and how the program was made.
WRITEUP.pdf- A PDF considering graphs made by UNIX tool displaying my results and my thoughts on them.
DESIGN.pdf- This is how I started thinking about how to code the program.
